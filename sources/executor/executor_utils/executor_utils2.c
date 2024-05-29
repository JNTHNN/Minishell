/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/24 11:08:09 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Loops through all IN redirections and opens fd's needed.
*/
static int	ft_open_in_loop(t_data *data, t_exec *exec, t_redir_lst	*current)
{
	while (current)
	{
		if (exec->fdin != NOT_INIT
			&& (current->r_type == IN || current->r_type == HEREDOC))
			close(exec->fdin);
		if (current->r_type == IN)
		{
			exec->fdin = open(current->filename, O_RDONLY);
			if (exec->fdin == F_ERROR)
			{
				if (data->nb_of_cmds != 1)
					exec->fdin = STDIN_FILENO;
				return (data->err_info = current->filename, E_OPEN);
			}
		}
		else if (current->r_type == HEREDOC)
		{
			exec->fdin = open(current->hd_path, O_RDONLY);
			if (exec->fdin == F_ERROR)
				return (data->err_info = current->filename, E_OPEN);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

/*
** Loops through all OUT redirections and opens fd's needed.
*/
static int	ft_open_out_loop(t_data *data, t_exec *exec, t_redir_lst *current)
{
	while (current)
	{
		if (exec->fdout != NOT_INIT
			&& (current->r_type == OUT || current->r_type == OUT_T))
			close(exec->fdout);
		if (current->r_type == OUT)
		{
			exec->fdout = open(current->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec->fdout == F_ERROR)
				return (data->err_info = current->filename, E_OPEN);
		}
		else if (current->r_type == OUT_T)
		{
			exec->fdout = open(current->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec->fdout == F_ERROR)
				return (data->err_info = current->filename, E_OPEN);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

/*
** Handles the logic for the opening of all IN redirection.
*/
int	ft_open_redir_in(t_data *data, t_cmd *cmd)
{
	t_redir_lst	*current;
	t_exec		*exec;

	exec = data->exec;
	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	if (ft_open_in_loop(data, exec, current))
		return (E_OPEN);
	if (exec->fdin != NOT_INIT)
	{
		if (dup2(exec->fdin, STDIN_FILENO) == F_ERROR)
			return (E_DUP);
		close(exec->fdin);
	}
	return (EXIT_SUCCESS);
}

/*
** Handles the logic for the opening of all OUT redirection.
*/
int	ft_open_redir_out(t_data *data, t_cmd *cmd)
{
	t_redir_lst	*current;
	t_exec		*exec;

	exec = data->exec;
	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	if (ft_open_out_loop(data, exec, current))
		return (E_OPEN);
	if (exec->fdout != NOT_INIT)
	{
		if (dup2(exec->fdout, STDOUT_FILENO) == F_ERROR)
			return (E_DUP);
		close(exec->fdout);
	}
	return (EXIT_SUCCESS);
}

/*
** Creates the child process for a lonely command. 
*/
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
		ft_restore_signals(false);
		ft_execute_command(data, data->cmd);
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
