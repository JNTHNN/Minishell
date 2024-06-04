/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/04 20:14:20 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if the path exists or points to a folder 
*/
void	ft_check_type(char *cmd, t_data *data, int flag)
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

/*
**	Setup error messages for execution
*/
void	ft_handle_exec_error(char *cmd, int code, t_data *data)
{
	data->err_info = cmd;
	if (ft_strchr(data->err_info, '/'))
		code = E_PATH;
	ft_handle_error(data, code);
}

/*
**	Check + launch the binary files (commands)
*/
int	ft_create_exec(t_data *data, t_cmd *cmd)
{
	char		**progpath;
	int			i;

	progpath = ft_path_abs(data, cmd);
	i = 0;
	if (!progpath)
		return (EXIT_FAILURE);
	if (!cmd->args[0][0])
		return (data->err_info = cmd->args[0], ft_handle_error(data, E_NOTF));
	while (progpath[i])
	{
		if (!access(progpath[i], F_OK | X_OK))
			if (execve(progpath[i], cmd->args, data->env) == -1)
				return (E_EXECVE);
		i++;
	}
	ft_free_array(progpath);
	ft_handle_exec_error(cmd->args[0], E_NOTF, data);
	return (EXIT_SUCCESS);
}

/*
**	Check if the commands is an absolute or relative path
*/
void	ft_execute_command(t_data *data, t_cmd *cmd)
{
	if (cmd->args && cmd->args[0])
	{
		if (ft_type_of_arg(cmd->args[0], cmd->data) == ABS)
		{
			ft_check_type(cmd->args[0], data, EXEC_ABS);
			if (execve(cmd->args[0], cmd->args, data->env) == -1)
				ft_handle_exec_error(cmd->args[0], E_EXECVE, data);
		}
		else if (ft_type_of_arg(cmd->args[0], cmd->data) == DOT
			|| ft_type_of_arg(cmd->args[0], cmd->data) == DIR)
		{
			if (ft_type_of_arg(cmd->args[0], cmd->data) == DIR)
			{
				ft_check_type(cmd->args[0], data, EXEC_REL);
				ft_handle_exec_error(cmd->args[0], E_PATH, data);
			}
			ft_handle_exec_error(cmd->args[0], E_NOTF, data);
		}
		else
			ft_relative_exec(data, cmd);
		ft_handle_exec_error(cmd->args[0], E_NOTF, data);
	}
}

t_exec	*ft_init_exec(t_data *data)
{
	t_exec		*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	exec->pipes = NULL;
	if (data->nb_of_cmds)
	{
		exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
		if (!exec->child_pid)
			ft_errno(ERR_MEM, EX_MISCERROR, data);
	}
	else
		exec->child_pid = NULL;
	exec->status = NOT_INIT;
	exec->tmpin = NOT_INIT;
	exec->tmpout = NOT_INIT;
	exec->fdin = NOT_INIT;
	exec->fdout = NOT_INIT;
	exec->trigger_hd = false;
	data->exec = exec;
	return (exec);
}
