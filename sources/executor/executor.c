/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/13 15:51:18 by jgasparo         ###   ########.fr       */
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
		return (ft_errno("fork", EXEC_FAIL, data), EXIT_FAILURE);
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
			ft_putendl_fd("^\\Quit: 3", STDERR_FILENO);
	}
	return (EXIT_SUCCESS);
}

int	ft_handle_heredoc(t_redir_lst *node)
{
	char	*line;
	int		fd;

	fd = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == F_ERROR)
		return (EXIT_FAILURE);
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

int	ft_trigger_heredoc(t_data *data)
{
	int			i;
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
					if (ft_handle_heredoc(current))
						return (EXIT_FAILURE);
				}
				current = current->next;
			}
		}
	}
	data->exec->trigger_hd = true;
	return (EXIT_SUCCESS);
}

int	ft_init_pipes(t_data *data, t_exec *exec)
{
	int	nb_of_pipes;
	int	i;

	nb_of_pipes = data->nb_of_cmds - 1;
	exec->pipes = (int **)malloc(nb_of_pipes * sizeof(int *));
	if (!exec->pipes)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	i = -1;
	while (++i < nb_of_pipes)
	{
		exec->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!exec->pipes[i])
			ft_errno(ERR_MEM, EX_MISCERROR, data);
		if (pipe(exec->pipes[i]) == F_ERROR)
			ft_errno(ERR_MEM, EX_MISCERROR, data);
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

int	ft_prepare_execution(t_data *data)
{
	t_exec		*exec;

	exec = ft_init_exec(data);
	if (!exec)
		return (E_MEM);
	ft_init_pipes(data, exec);
	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	if (exec->tmpin == F_ERROR || exec->tmpout == F_ERROR)
		return (E_DUP);
	return (EXIT_SUCCESS);
}

int	ft_exec_one_cmd(t_data *data)
{
	if (ft_trigger_heredoc(data))
		return (E_OPEN);
	if (ft_open_redir_in(data, data->cmd) || ft_open_redir_out(data, data->cmd))
		return (E_OPEN);
	if (!data->cmd->is_builtin)
		ft_cmd_exec(data);
	else
		ft_builtin(data, data->cmd);
	if (dup2(data->exec->tmpin, STDIN_FILENO) == F_ERROR)
		return (E_DUP);
	if (dup2(data->exec->tmpout, STDOUT_FILENO) == F_ERROR)
		return (E_DUP);
	if (close(data->exec->tmpin) == F_ERROR
		|| close(data->exec->tmpout) == F_ERROR)
		return (E_CLOSE);
	return (EXIT_SUCCESS);
}

int	ft_executor(t_data *data)
{
	t_cmd		*current_cmd;
	int			i;
	int			ret;

	i = 0;
	ret = ft_prepare_execution(data);
	if (ret)
		return (ret);
	if (data->nb_of_cmds == 1)
	{
		ret = ft_exec_one_cmd(data);
		if (ret)
			return (ret);
	}
	else
	{
		current_cmd = data->cmd;
		while (current_cmd)
		{
			if (data->exec->trigger_hd == false)
				ft_trigger_heredoc(data);
			data->exec->child_pid[i] = fork();
			data->exec->status = 0;
			if (data->exec->child_pid[i] == F_ERROR)
				perror("fork");
			if (data->exec->child_pid[i] == FORKED_CHILD)
			{
				if (ft_open_redir_in(data, current_cmd)
					|| ft_open_redir_out(data, current_cmd))
					return (E_OPEN);
				if (current_cmd->left && data->exec->fdin == NOT_INIT)
				{
					if (dup2(data->exec->pipes[i - 1][0], STDIN_FILENO) == F_ERROR)
						return (E_DUP);
					close(data->exec->pipes[i - 1][1]);
				}
				if (current_cmd->right && data->exec->fdout == NOT_INIT)
				{
					if (dup2(data->exec->pipes[i][1], STDOUT_FILENO) == F_ERROR)
						return (E_DUP);
					close(data->exec->pipes[i][0]);
				}
				if (!current_cmd->right && data->exec->fdout == NOT_INIT)
					dup2(data->exec->tmpout, STDOUT_FILENO);
				ft_close_pipes(data, data->exec, i);
				if (!current_cmd->is_builtin)
				{
					ft_signal(SIG_DFL);
					execute_command(data, current_cmd);
				}
				else
					ft_builtin(data, current_cmd);
				exit(EXIT_SUCCESS);
			}
			i++;
			if (current_cmd->right)
				g_exit_code = EXIT_SUCCESS;
			current_cmd = current_cmd->right;
			data->exec->fdin = -1;
			data->exec->fdout = -1;
		}
		// Close all parent pipes ends
		int j = -1;
		while (++j < data->nb_of_cmds - 1)
		{
			close(data->exec->pipes[j][0]);
			close(data->exec->pipes[j][1]);
		}

		// restore std i/o
		dup2(data->exec->tmpin, STDIN_FILENO);
		dup2(data->exec->tmpout, STDOUT_FILENO);
		close(data->exec->tmpin);
		close(data->exec->tmpout);
	}
	bool one = false; // a mieux init
	while (i--)
	{
		data->exec->child_pid[i] = waitpid(0, &data->exec->status, 0);
		if (WIFEXITED(data->exec->status))
			g_exit_code = WEXITSTATUS(data->exec->status);
		if (WIFSIGNALED(data->exec->status) && data->exec->status != SIGPIPE && !one)
		{
			ft_putendl_fd("^\\Quit: 3", STDERR_FILENO);
			one = true;
		}
	}
	return (EXIT_SUCCESS);
}
