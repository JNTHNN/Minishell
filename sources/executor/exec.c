/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/10 14:18:44 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_exec(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == F_ERROR)
	// {
	// 	perror("fork");
	// 	return (EXIT_FAILURE);
	// }
		return (ft_errno("fork", 1, data, false), EXIT_FAILURE);
	else if (pid == FORKED_CHILD)
	{
		ft_signal(SIG_DFL);
		execute_command(data, data->cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			printf("^\\Quit: %d\n", SIGQUIT);
	}
	return (EXIT_SUCCESS);
}

int	ft_open_redir_in(t_data *data, t_cmd *cmd, t_exec *exec)
{
	t_redir_lst	*current;

	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	while (current)
	{
		if (current->r_type == IN)
		{
			exec->fdin = open(current->filename, O_RDONLY);
			if (exec->fdin == -1)
				return (data->err_info = current->filename, E_OPEN);
		}
		else if (current->r_type == HEREDOC)
		{
			exec->fdin = open(current->hd_path, O_RDONLY);
			if (exec->fdin == -1)
				return (data->err_info = current->filename, E_OPEN);
		}
		current = current->next;
	}
	if (exec->fdin != -1)
	{
		if (dup2(exec->fdin, STDIN_FILENO) == -1)
			return (E_DUP);
		close(exec->fdin);
	}
	return (EXIT_SUCCESS);
}

int	ft_open_redir_out(t_data *data, t_cmd *cmd, t_exec *exec)
{
	t_redir_lst	*current;

	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	while (current)
	{
		if (current->r_type == OUT)
		{
			exec->fdout = open(current->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec->fdout == -1)
			{
				perror(current->filename);
				return (data->err_info = current->filename, E_OPEN);
			}
		}
		else if (current->r_type == OUT_T)
		{
			exec->fdout = open(current->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec->fdout == -1)
				return (data->err_info = current->filename, E_OPEN);
		}
		current = current->next;
	}
	if (exec->fdout != -1)
	{
		if (dup2(exec->fdout, STDOUT_FILENO) == -1)
			return (E_DUP);
		close(exec->fdout);
	}
	return (EXIT_SUCCESS);
}

int	ft_handle_heredoc(t_redir_lst *node)
{
	char	*line;
	int		fd;

	fd = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (E_OPEN);
	while (true)
	{
		line = readline("> ");
		if (ft_strncmp(line, node->filename, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
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
					ret = ft_handle_heredoc(current);
					if (ret)
						return (ret);
				}
				current = current->next;
			}
		}
	}
	exec->trigger_hd = true;
	return (EXIT_SUCCESS);
}

int	ft_init_pipes(t_data *data, t_exec *exec)
{
	int	nb_of_pipes;
	int	i;

	nb_of_pipes = data->nb_of_cmds - 1;
	exec->pipes = (int **)malloc(nb_of_pipes * sizeof(int *));
	if (!exec->pipes)
		return (E_MEM);
	i = -1;
	while (++i < nb_of_pipes)
	{
		exec->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!exec->pipes[i])
			return (E_MEM);
		if (pipe(exec->pipes[i]) == F_ERROR)
			return (E_MEM);
	}
	return (EXIT_SUCCESS);
}

void	ft_close_pipes(t_data *data, t_exec *exec, int skip)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = data->nb_of_cmds - 1;
	while (i < nb_pipes)
	{
		if (i == skip)
			i++;
		if (i == nb_pipes)
			break ;
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}

int	ft_executor(t_data *data)
{
	t_exec		*exec;
	t_cmd		*current_cmd;
	int			i;

	i = 0;
	exec = ft_init_exec(data);
	if (!exec)
		return (E_MEM);
	g_exit_code = ft_init_pipes(data, exec);
	if (g_exit_code)
		return (g_exit_code);
	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	if (exec->tmpin == -1 || exec->tmpout == -1)
		return (E_DUP);
	if (data->nb_of_cmds == 1)
	{
		ft_trigger_heredoc(data, exec);
		g_exit_code = ft_open_redir_in(data, data->cmd, exec);
		if (g_exit_code)
			return (g_exit_code);
		g_exit_code = ft_open_redir_out(data, data->cmd, exec);
		if (g_exit_code)
			return (g_exit_code);
		if (!g_exit_code)
		{
			if (!data->cmd->is_builtin)
				ft_cmd_exec(data);
			else
				ft_builtin(data, data->cmd);
		}
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
			if (exec->trigger_hd == false)
				ft_trigger_heredoc(data, exec);
			exec->child_pid[i] = fork();
			exec->status = 0;
			if (exec->child_pid[i] == F_ERROR)
				perror("fork");
			if (exec->child_pid[i] == FORKED_CHILD)
			{
				g_exit_code = ft_open_redir_in(data, current_cmd, exec);
				if (g_exit_code)
					return (g_exit_code);
				g_exit_code = ft_open_redir_out(data, current_cmd, exec);
				if (g_exit_code)
					return (g_exit_code);
				if (current_cmd->left && exec->fdin == NOT_INIT)
				{
					if (dup2(exec->pipes[i - 1][0], STDIN_FILENO) == F_ERROR)
						return (E_DUP);
					close(exec->pipes[i - 1][1]);
					ft_close_pipes(data, exec, i);
				}
				if (current_cmd->right && exec->fdout == NOT_INIT)
				{
					if (dup2(exec->pipes[i][1], STDOUT_FILENO) == F_ERROR)
						return (E_DUP);
					close(exec->pipes[i][0]);
					ft_close_pipes(data, exec, i);
				}
				if (!current_cmd->right && exec->fdout == NOT_INIT)
					dup2(exec->tmpout, STDOUT_FILENO);
				if (!current_cmd->is_builtin)
					execute_command(data, current_cmd);
				else
					ft_builtin(data, current_cmd);
				exit(EXIT_SUCCESS);
			}
			i++;
			current_cmd = current_cmd->right;
			exec->fdin = -1;
			exec->fdout = -1;
		}
		// Close all parent pipes ends
		int j = -1;
		while (++j < data->nb_of_cmds - 1)
		{
			close(exec->pipes[j][0]);
			close(exec->pipes[j][1]);
		}

		// restore std i/o
		dup2(exec->tmpin, STDIN_FILENO);
		dup2(exec->tmpout, STDOUT_FILENO);
		close(exec->tmpin);
		close(exec->tmpout);
	}
	while (i--)
	{
		exec->child_pid[i] = waitpid(0, &exec->status, 0);
		if (WIFEXITED(exec->status))
			g_exit_code = WEXITSTATUS(exec->status);
	}
	// if (WIFSIGNALED(exec->status))
	// 	printf("^\\Quit: %d\n", SIGQUIT);
	return (EXIT_SUCCESS);
}

// FREE PIPES HERE OR IN CLEAN, ETC.