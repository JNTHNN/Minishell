/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/29 08:24:24 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles the pipe logic between all commands.
*/
static int	ft_handle_pipes(t_data *data, t_cmd *cmd, int *nb)
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
		if (close(data->exec->pipes[*nb][1]) == F_ERROR)
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

/*
** Handles the child process to execute each command in multiple commands loop.
*/
static int	ft_child_process(t_data *data, t_cmd *cmd, int *nb)
{
	int	ret;

	if (ft_open_first_redir(data, cmd))
		ft_handle_error(data, E_OPEN);
	ret = ft_handle_pipes(data, cmd, nb);
	if (ret)
		return (ret);
	if (!cmd->is_builtin)
	{
		ft_restore_signals(false);
		ft_execute_command(data, cmd);
	}
	else
		ft_builtin(data, cmd);
	ft_free_data(data);
	return (exit(EXIT_SUCCESS), EXIT_SUCCESS);
}

/*
** Resets the exec fdin and fdout for the next command.
*/
static void	ft_reset_fdio(t_data *data, t_cmd *cmd)
{
	if (cmd->right)
		g_exit_code = EXIT_SUCCESS;
	data->exec->fdin = -1;
	data->exec->fdout = -1;
}

/*
** Handles the logic for multiple commands.
*/
int	ft_exec_cmds_loop(t_data *data, int *nb)
{
	t_cmd	*current_cmd;
	int		ret;

	current_cmd = data->cmd;
	while (current_cmd)
	{
		ret = ft_check_heredoc(data);
		if (ret == E_OPEN)
			return (ret);
		if (ret == EXIT_HD || ret == CTRL_D)
			return (EXIT_SUCCESS);
		data->exec->child_pid[*nb] = fork();
		data->exec->status = 0;
		if (data->exec->child_pid[*nb] == F_ERROR)
			ft_errno(ERR_FORK, EXEC_FAIL, data);
		if (data->exec->child_pid[*nb] == FORKED_CHILD)
			ret = ft_child_process(data, current_cmd, nb);
		if (ret)
			return (ret);
		ft_reset_fdio(data, current_cmd);
		(*nb)++;
		current_cmd = current_cmd->right;
	}
	return (EXIT_SUCCESS);
}

/*
** Creates path to the command binary file for each env path.
*/
char	**ft_pathiter(char **path, t_cmd *cmd)
{
	char	*new_cmd;
	char	*temp;

	new_cmd = ft_strjoin("/", cmd->args[0]);
	while (path && *path)
	{
		temp = ft_strjoin(*path, new_cmd);
		free(*path);
		*path = ft_strdup(temp);
		free(temp);
		path++;
	}
	free(new_cmd);
	return (path);
}
