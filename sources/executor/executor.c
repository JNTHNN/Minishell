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

#include "minishell.h"

void	ft_restore_signals(void)
{
	struct termios	term;

	ft_signal(SIG_DFL);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_print_signals(int status)
{
	if (status == SIGQUIT)
	{
		ft_putendl_fd(STR_QUIT, STDERR_FILENO);
		g_exit_code = 131;
	}
	else
	{
		printf(CLEAR_LINE);
		g_exit_code = 130;
	}
}

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
		ft_restore_signals();
		execute_command(data, data->cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			ft_print_signals(status);
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

int	ft_close_pipes(t_data *data, t_exec *exec, int skip)
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
		if (close(exec->pipes[i][0]) == F_ERROR)
			return (E_CLOSE);
		if (i != skip - 1)
		{
			if (close(exec->pipes[i][1]) == F_ERROR)
				return (E_CLOSE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
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

int	ft_exec_simple_cmd(t_data *data)
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

void	ft_wait_children(t_data * data, int *children_nb)
{
	bool	first_child;
	t_exec	*exec;

	first_child = false;
	exec = data->exec;
	while ((*children_nb)--)
	{
		exec->child_pid[*children_nb] = waitpid(0, &exec->status, 0);
		if (WIFEXITED(exec->status))
			g_exit_code = WEXITSTATUS(data->exec->status);
		if (WIFSIGNALED(exec->status) && exec->status
			!= SIGPIPE && !first_child)
		{
			ft_print_signals(exec->status);
			first_child = true;
		}
	}
}

int	ft_close_pipes_in_parent(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_cmds - 1)
	{
		if (close(data->exec->pipes[i][0]) == F_ERROR
			|| close(data->exec->pipes[i][1]) == F_ERROR)
			return (E_CLOSE);
	}
	return (EXIT_SUCCESS);
}

int	ft_reset_stdio(t_data *data)
{
	if (dup2(data->exec->tmpin, STDIN_FILENO) == F_ERROR
		|| dup2(data->exec->tmpout, STDOUT_FILENO) == F_ERROR)
		return (E_DUP);
	if (close(data->exec->tmpin) == F_ERROR
		|| close(data->exec->tmpout) == F_ERROR)
		return (E_CLOSE);
	return (EXIT_SUCCESS);
}

int	ft_handle_pipes(t_data *data, t_cmd *cmd, int *nb)
{
	if (cmd->left && data->exec->fdin == NOT_INIT)
	{
		if (dup2(data->exec->pipes[(*nb) - 1][0], STDIN_FILENO) == F_ERROR)
			return (E_DUP);
		if (close(data->exec->pipes[(*nb) - 1][1]) == F_ERROR)
			return (E_CLOSE);
	}
	if (cmd->right && data->exec->fdout == NOT_INIT)
	{
		if (dup2(data->exec->pipes[*nb][1], STDOUT_FILENO) == F_ERROR)
			return (E_DUP);
		if (close(data->exec->pipes[*nb][0]) == F_ERROR)
			return (E_CLOSE);
	}
	if (!cmd->right && data->exec->fdout == NOT_INIT)
	{
		if (dup2(data->exec->tmpout, STDOUT_FILENO) == F_ERROR)
			return (E_DUP);
	}
	if (ft_close_pipes(data, data->exec, *nb) == E_CLOSE)
		return (E_CLOSE);
	return (EXIT_SUCCESS);
}

int ft_child_process(t_data *data, t_cmd *cmd, int *nb)
{
	int	ret;

	if (ft_open_redir_in(data, cmd) || ft_open_redir_out(data, cmd))
		return (E_OPEN);
	ret = ft_handle_pipes(data, cmd, nb);
	if (ret)
		return (ret);
	if (!cmd->is_builtin)
	{
		ft_restore_signals();
		execute_command(data, cmd);
	}
	else
		ft_builtin(data, cmd);
	return (exit(EXIT_SUCCESS), EXIT_SUCCESS);
}

void ft_reset_fdio(t_data *data, t_cmd *cmd)
{
	if (cmd->right)
		g_exit_code = EXIT_SUCCESS;
	data->exec->fdin = -1;
	data->exec->fdout = -1;
}

int ft_exec_cmds_loop(t_data * data, int *nb)
{
	t_cmd	*current_cmd;
	int		ret;

	current_cmd = data->cmd;
	while (current_cmd)
	{
		if (data->exec->trigger_hd == false)
			ft_trigger_heredoc(data);
		data->exec->child_pid[*nb] = fork();
		data->exec->status = 0;
		if (data->exec->child_pid[*nb] == F_ERROR)
			ft_errno(ERR_FORK, EXEC_FAIL, data);
		if (data->exec->child_pid[*nb] == FORKED_CHILD)
		{
			ret = ft_child_process(data, current_cmd, nb);
			if (ret)
				return (ret);
		}
		ft_reset_fdio(data, current_cmd);
		(*nb)++;
		current_cmd = current_cmd->right;
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_multiple_cmds(t_data *data, int *cmd_nb)
{
	int	ret;

	ret = ft_exec_cmds_loop(data, cmd_nb);
	if (ret)
		return (ret);
	ret = ft_close_pipes_in_parent(data);
	if (ret)
		return (ret);
	ret = ft_reset_stdio(data);
	if (ret)
		return (ret);
	return (EXIT_SUCCESS);
}

int	ft_executor(t_data *data)
{
	int			i;
	int			ret;

	i = 0;
	ret = ft_prepare_execution(data);
	if (ret)
		return (ret);
	if (data->nb_of_cmds == 1)
	{
		ret = ft_exec_simple_cmd(data);
		if (ret)
			return (ret);
	}
	else
	{
		ret = ft_exec_multiple_cmds(data, &i);
		if (ret)
			return (ret);
	}
	ft_wait_children(data, &i);
	return (EXIT_SUCCESS);
}
