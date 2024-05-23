/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:01:12 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_in_loop(t_data *data, t_exec *exec, t_redir_lst	*current)
{
	while (current)
	{
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

static int	ft_open_out_loop(t_data *data, t_exec *exec, t_redir_lst *current)
{
	while (current)
	{
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

int	ft_open_redir_in(t_data *data, t_cmd *cmd, int *nb)
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
		if (close(data->exec->pipes[*nb][1]) == F_ERROR)
			return (E_CLOSE);
		if (close(data->exec->pipes[*nb][0]) == F_ERROR)
			return (E_CLOSE);
	}
	return (EXIT_SUCCESS);
}

int	ft_open_redir_out(t_data *data, t_cmd *cmd, int *nb)
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
		if (close(data->exec->pipes[*nb][0]) == F_ERROR)
			return (E_CLOSE);
		if (close(data->exec->pipes[*nb][1]) == F_ERROR)
			return (E_CLOSE);
	}
	return (EXIT_SUCCESS);
}
