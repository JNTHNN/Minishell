/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/16 12:38:38 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_type(char *cmd, t_data *data, int flag)
{
	struct stat	s_stat;

	if (!lstat(cmd, &s_stat) && S_ISDIR(s_stat.st_mode))
	{
		if (S_ISDIR(s_stat.st_mode))
		{
			data->err_info = cmd;
			ft_handle_error(data, E_DIR);
		}
	}
	if (flag == EXEC_ABS)
	{
		if (access(cmd, F_OK | X_OK))
		{
			data->err_info = cmd;
			if (errno == ENOENT)
				ft_handle_error(data, E_EXECVE_2);
			ft_handle_error(data, E_EXECVE);
		}
	}
}

static void	ft_handle_exec_error(char *cmd, int code, t_data *data)
{
	data->err_info = cmd;
	ft_handle_error(data, code);
}

int	ft_create_exec(t_data *data, t_cmd *cmd)
{
	char		**progpath;
	int			i;
	struct stat	s_stat;

	progpath = ft_path_abs(data, cmd);
	i = 0;
	if (!progpath)
		return (EXIT_FAILURE);
	if (!cmd->args[0][0])
		return (data->err_info = cmd->args[0], ft_handle_error(data, E_NOTF));
	while (progpath[i])
	{
		if (!access(progpath[i], F_OK | X_OK))
		{
			if (execve(progpath[i], cmd->args, data->env) == -1)
				return (E_EXECVE);
		}
		i++;
	}
	ft_free_array(progpath);
	if (!lstat(cmd->args[0], &s_stat) && S_ISDIR(s_stat.st_mode))
		return (E_NOTF);
	return (EXIT_SUCCESS);
}

void	ft_execute_command(t_data *data, t_cmd *cmd)
{
	int			ret;

	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], "/", 1)
			|| !ft_strncmp(cmd->args[0], "./", 2))
		{
			ft_check_type(cmd->args[0], data, EXEC_ABS);
			if (execve(cmd->args[0], cmd->args, data->env) == -1)
				ft_handle_exec_error(cmd->args[0], E_EXECVE, data);
		}
		else
		{
			ret = ft_create_exec(data, cmd);
			if (ret)
				ft_handle_exec_error(cmd->args[0], ret, data);
			ft_check_type(cmd->args[0], data, EXEC_REL);
		}
		data->err_info = cmd->args[0];
		ft_handle_error(data, E_NOTF);
	}
}

t_exec	*ft_init_exec(t_data *data)
{
	t_exec		*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	exec->pipes = NULL;
	exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
	if (!exec->child_pid)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	exec->status = NOT_INIT;
	exec->tmpin = NOT_INIT;
	exec->tmpout = NOT_INIT;
	exec->fdin = NOT_INIT;
	exec->fdout = NOT_INIT;
	exec->trigger_hd = false;
	data->exec = exec;
	return (exec);
}
