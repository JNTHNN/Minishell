/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/29 08:01:18 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_prepare_execution(t_data *data)
{
	t_exec		*exec;

	exec = ft_init_exec(data);
	if (exec)
	{
		exec->tmpin = dup(STDIN_FILENO);
		exec->tmpout = dup(STDOUT_FILENO);
		if (exec->tmpin == F_ERROR || exec->tmpout == F_ERROR)
			return (E_DUP);
	}
	return (EXIT_SUCCESS);
}

static int	ft_exec_simple_cmd(t_data *data)
{
	int	ret;

	ret = ft_trigger_heredoc(data);
	if (ret == E_OPEN)
		return (E_OPEN);
	if (ret == EXIT_HD || ret == CTRL_D)
		return (EXIT_SUCCESS);
	if (ft_open_redir_in(data, data->cmd)
		|| ft_open_redir_out(data, data->cmd))
		return (E_OPEN);
	if (!data->cmd->is_builtin && data->cmd->args)
		ft_cmd_exec(data);
	else if (data->cmd->is_builtin)
		ft_builtin(data, data->cmd);
	if (data->exec)
	{
		if (dup2(data->exec->tmpin, STDIN_FILENO) == F_ERROR)
			return (E_DUP);
		if (dup2(data->exec->tmpout, STDOUT_FILENO) == F_ERROR)
			return (E_DUP);
		if (close(data->exec->tmpin) == F_ERROR
			|| close(data->exec->tmpout) == F_ERROR)
			return (E_CLOSE);
	}
	return (EXIT_SUCCESS);
}

static void	ft_wait_children(t_data *data, int *children_nb)
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

static int	ft_exec_multiple_cmds(t_data *data, int *cmd_nb)
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
		ft_init_pipes(data, data->exec);
		ret = ft_exec_multiple_cmds(data, &i);
		if (ret)
			return (ret);
	}
	ft_wait_children(data, &i);
	return (EXIT_SUCCESS);
}
