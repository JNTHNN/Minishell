/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/15 10:49:08 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	execute_command(t_data *data, t_cmd *cmd)
{
	int			ret;
	struct stat	s_stat;

	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], "/", 1)
			|| !ft_strncmp(cmd->args[0], "./", 2)) // si ca commence par ./exe ou /exe 126
		{
			if (!lstat(cmd->args[0], &s_stat) && S_ISDIR(s_stat.st_mode))
			{
				data->err_info = cmd->args[0];
				ft_handle_error(data, E_DIR);
			}
			if (access(cmd->args[0], F_OK | X_OK))
			{
				data->err_info = cmd->args[0];
				if (errno == ENOENT)
					ft_handle_error(data, E_EXECVE_2);
				ft_handle_error(data, E_EXECVE);
			}
			else
			{
				if (execve(cmd->args[0], cmd->args, data->env) == -1)
				{
					data->err_info = cmd->args[0];
					ft_handle_error(data, E_EXECVE);
				}
			}
		}
		else // direct exe
		{
			// check path
			ret = ft_create_exec(data, cmd);
			if (ret)
			{
				data->err_info = cmd->args[0];
				ft_handle_error(data, ret);
			}
			// check si doss
			if (!lstat(cmd->args[0], &s_stat) && S_ISDIR(s_stat.st_mode))
			{
				data->err_info = cmd->args[0];
				ft_handle_error(data, E_DIR);
			}
		}
		data->err_info = cmd->args[0];
		ft_handle_error(data, E_NOTF);
	}
}

char	**ft_pathiter(char **path, t_cmd *cmd)
{
	char	*new_cmd;
	char	*temp;

	new_cmd = ft_strjoin("/", cmd->args[0]);
	while (path && *path)
	{
		temp = ft_strjoin(*path, new_cmd);
		*path = temp;
		path++;
	}
	return (path);
}

char	**ft_path_abs(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**my_path;

	path = ft_getenv(data, "PATH");
	my_path = ft_split(path, ':');
	ft_pathiter(my_path, cmd);
	return (my_path);
}

int	ft_create_exec(t_data *data, t_cmd *cmd)
{
	char	**progpath;
	int		i;

	progpath = ft_path_abs(data, cmd);
	i = 0;
	if (!progpath)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

t_exec	*ft_init_exec(t_data *data)
{
	t_exec		*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		ft_errno(ERR_MEM, 2, data);
	exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
	if (!exec->child_pid)
		ft_errno(ERR_MEM, 2, data);
	exec->status = -1;
	exec->tmpin = -1;
	exec->tmpout = -1;
	exec->fdin = -1;
	exec->fdout = -1;
	exec->trigger_hd = false;
	data->exec = exec;
	return (exec);
}
