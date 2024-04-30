/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/29 17:13:22 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_exec(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			printf("^\\Quit: %d\n", SIGQUIT);
	}
	else
	{
		ft_signal(SIG_DFL);
		execute_command(data, data->cmd);
	}
	return (EXIT_SUCCESS);
}

t_redir_lst	*ft_find_last_redir(t_redir_lst **lst, t_redirect_type type)
{
	t_redir_lst	*is_last;
	t_redir_lst	*temp;

	is_last = NULL;
	if (!*lst)
		return (NULL);
	temp = *lst;
	while (temp)
	{
		if (temp->r_type == type)
			is_last = temp;
		temp = temp->next;
	}
	return (is_last);
}

int	ft_fill_last_redir(t_cmd *cmd, t_exec *exec)
{
	if (cmd->redirections)
	{
		exec->last_r->in = ft_find_last_redir(&cmd->redirections, IN);
		exec->last_r->out = ft_find_last_redir(&cmd->redirections, OUT);
		exec->last_r->out_t = ft_find_last_redir(&cmd->redirections, OUT_T);
		exec->last_r->hd = ft_find_last_redir(&cmd->redirections, HEREDOC);
	}
	return (EXIT_SUCCESS);
}

t_redir_lst	*ft_last_heredoc(t_data *data)
{
	int			i;
	t_redir_lst	*current;
	t_redir_lst	*last;

	last = NULL;
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		if (data->redirections[i])
		{
			current = data->redirections[i];
			while (current != NULL)
			{
				if (current->r_type == HEREDOC)
					last = current;
				current = current->next;
			}
		}
	}
	return (last);
}

int	ft_handle_heredoc(t_data *data, t_redir_lst *node, t_exec *exec)
{
	char	*line;

	exec->fdout = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->fdout == -1)
		return (E_OPEN);
	while (true)
	{
		line = readline("> ");
		if (ft_strncmp(line, node->filename, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, exec->fdout);
		free(line);
	}
	free(line);
	close(exec->fdout);
	if (node == ft_last_heredoc(data))
	{
		exec->fdin = open(node->hd_path, O_RDONLY);
		if (exec->fdin == -1)
			return (E_OPEN);
		if (dup2(exec->fdin, STDIN_FILENO) == -1)
			return (E_DUP);
		close(exec->fdin);
	}
	return (EXIT_SUCCESS);
}

int	ft_trigger_heredoc(t_data *data, t_exec *exec)
{
	int			i;
	int			ret;
	t_redir_lst	*current;

	i = -1;
	while (++i < data->nb_of_cmds)
	{
		if (data->redirections[i])
		{
			current = data->redirections[i];
			while (current != NULL)
			{
				if (current->r_type == HEREDOC)
				{
					ret = ft_handle_heredoc(data, current, exec);
					if (ret)
						return (ret);
				}
				current = current->next;
			}
		}
	}
	return (EXIT_SUCCESS);
}


int	ft_executor(t_data *data)
{
	t_exec		*exec;
	t_cmd		*current_cmd;
	pid_t		*pid = NULL;
	int			i = 0;

	pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
	exec = ft_init_exec(data);
	if (!exec)
		return (E_MEM);
	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	if (exec->tmpin == -1 || exec->tmpout == -1)
		return (E_DUP);
	if (data->nb_of_cmds == 1)
	{
		ft_fill_last_redir(data->cmd, exec);
		ft_trigger_heredoc(data, exec);
		if (exec->last_r->in)
		{
			if (!exec->last_r->hd
				|| (exec->last_r->hd && exec->last_r->hd->id < exec->last_r->in->id))
			{
				exec->fdin = open(exec->last_r->in->filename, O_RDONLY);
				if (exec->fdin == -1)
				{
					data->err_info = exec->last_r->in->filename;
					return (E_OPEN);
				}
				if (dup2(exec->fdin, STDIN_FILENO) == -1)
					return (E_DUP);
				close(exec->fdin);
			}
		}
		if (exec->last_r->out)
		{
			exec->fdout = open(exec->last_r->out->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec->fdout == -1)
			{
				data->err_info = exec->last_r->out->filename;
				return (E_OPEN);
			}
			if (dup2(exec->fdout, STDOUT_FILENO) == -1)
				return (E_DUP);
			close(exec->fdout);
		}
		if (exec->last_r->out_t)
		{
			exec->fdout = open(exec->last_r->out_t->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec->fdout == -1)
			{
				data->err_info = exec->last_r->out_t->filename;
				return (E_OPEN);
			}
			if (dup2(exec->fdout, STDOUT_FILENO) == -1)
				return (E_DUP);
			close(exec->fdout);
		}
		if (!data->cmd->is_builtin)
			ft_cmd_exec(data);
		else
			ft_builtin(data, data->cmd);
		if (dup2(exec->tmpin, STDIN_FILENO) == -1)
			return (E_DUP);
		if (dup2(exec->tmpout, STDOUT_FILENO) == -1)
			return (E_DUP);
		close(exec->tmpin);
		close(exec->tmpout);
	}
	else
	{
		current_cmd = data->cmd;
		while (current_cmd)
		{
			ft_fill_last_redir(current_cmd, exec);
			ft_trigger_heredoc(data, exec);
			if (current_cmd->left)
			{
				dup2(exec->pipe_fd[0], STDIN_FILENO);
				// close(exec->pipe_fd[0]);
				fprintf(stderr, "L PID [%d] ID [%d] STATUS [%d] PIPE0[%d] PIPE1[%d] FD IN[%d] FD OUT[%d] TMPIN [%d] TMPOUT [%d]\n", pid[i], i, exec->status, exec->pipe_fd[0], exec->pipe_fd[1], exec->fdin, exec->fdout, exec->tmpin, exec->tmpout);
			}
			if (!current_cmd->right)
			{
				dup2(exec->tmpout, exec->pipe_fd[1]);
				close(exec->tmpout);
				// exec->pipe_fd[1] = dup(exec->tmpout); // ajouter outfile ici
				fprintf(stderr, "R PID [%d] ID [%d] STATUS [%d] PIPE0[%d] PIPE1[%d] FD IN[%d] FD OUT[%d] TMPIN [%d] TMPOUT [%d]\n", pid[i], i, exec->status, exec->pipe_fd[0], exec->pipe_fd[1], exec->fdin, exec->fdout, exec->tmpin, exec->tmpout);
			}
			else
			{
				pipe(exec->pipe_fd);
				// exec->fdin = exec->pipe_fd[0];
				// exec->fdout = exec->pipe_fd[1];
			}
			fprintf(stderr, "AV PID [%d] ID [%d] STATUS [%d] PIPE0[%d] PIPE1[%d] FD IN[%d] FD OUT[%d] TMPIN [%d] TMPOUT [%d]\n", pid[i], i, exec->status, exec->pipe_fd[0], exec->pipe_fd[1], exec->fdin, exec->fdout, exec->tmpin, exec->tmpout);
			if (dup2(exec->pipe_fd[1], STDOUT_FILENO) == -1)
				return (E_DUP);
			fprintf(stderr, "AP PID [%d] ID [%d] STATUS [%d] PIPE0[%d] PIPE1[%d] FD IN[%d] FD OUT[%d] TMPIN [%d] TMPOUT [%d]\n", pid[i], i, exec->status, exec->pipe_fd[0], exec->pipe_fd[1], exec->fdin, exec->fdout, exec->tmpin, exec->tmpout);
			close(exec->pipe_fd[1]);
			pid[i] = fork();
			fprintf(stderr, "F PID [%d] ID [%d] STATUS [%d] PIPE0[%d] PIPE1[%d] FD IN[%d] FD OUT[%d] TMPIN [%d] TMPOUT [%d]\n", pid[i], i, exec->status, exec->pipe_fd[0], exec->pipe_fd[1], exec->fdin, exec->fdout, exec->tmpin, exec->tmpout);
			exec->status = 0;
			if (pid[i] == -1)
				perror("fork");
			if (pid[i] == 0)
			{
				if (!current_cmd->is_builtin)
					execute_command(data, current_cmd);
				else
					ft_builtin(data, current_cmd);
				exit(EXIT_SUCCESS);
			}
			current_cmd = current_cmd->right;
			i++;
		}
		dup2(exec->tmpin, STDIN_FILENO);
		dup2(exec->tmpout, STDOUT_FILENO);
		close(exec->tmpin);
		close(exec->tmpout);
		close(exec->fdin);
		close(exec->fdout);
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
		
	}
	pid_t tmp;
	while (i--)
	{
		dup2(exec->tmpout, exec->pipe_fd[1]);
		tmp = waitpid(0, &exec->status, 0);
		fprintf(stderr, "W PID [%d] ID [%d] STATUS [%d] PIPE0[%d] PIPE1[%d] FD IN[%d] FD OUT[%d] TMPIN [%d] TMPOUT [%d]\n", tmp, i, exec->status, exec->pipe_fd[0], exec->pipe_fd[1], exec->fdin, exec->fdout, exec->tmpin, exec->tmpout);
	}
	if (WIFSIGNALED(exec->status))
		printf("^\\Quit: %d\n", SIGQUIT);
	return (EXIT_SUCCESS);
}
