/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:29:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/29 11:03:56 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees memory allocated for the pipes array 
** and closes the pipe file descriptors.
*/
static void	ft_free_pipes(t_data *data, t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_cmds - 1)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		free(exec->pipes[i]);
		exec->pipes[i] = NULL;
	}
	if (exec->pipes)
	{
		free(exec->pipes);
		exec->pipes = NULL;
	}
}

/*
** Frees memory allocated for the exec structure 
** and closes related file descriptors.
*/
void	ft_free_exec(t_data *data)
{
	if (data && data->exec)
	{
		if (data->exec && data->exec->pipes)
			ft_free_pipes(data, data->exec);
		if (data->exec && data->exec->child_pid)
		{
			free(data->exec->child_pid);
			data->exec->child_pid = NULL;
		}
		if (data->exec->fdin != NOT_INIT)
			close(data->exec->fdin);
		if (data->exec->fdout != NOT_INIT)
			close(data->exec->fdout);
		if (data->exec->tmpin != NOT_INIT)
			close(data->exec->tmpin);
		if (data->exec->tmpout != NOT_INIT)
			close(data->exec->tmpout);
		free(data->exec);
		data->exec = NULL;
	}
}

/*
** Frees memory allocated in case of error
** during the program execution.
*/
void	ft_free_if_error(t_data *data)
{
	if (data)
	{
		if (data->input)
		{
			free(data->input);
			data->input = NULL;
		}
		if (data->tokens)
			ft_free_tokens(&data->tokens);
		if (data->cmd)
			ft_free_cmds(&data->cmd);
		if (data->redirections)
		{
			free(data->redirections);
			data->redirections = NULL;
		}
		if (data->exec)
			ft_free_exec(data);
	}
}

/*
** Resets the data structure for the next command execution.
*/
void	ft_reset_data(t_data *data)
{
	if (data->tokens)
		ft_free_tokens(&data->tokens);
	ft_free_cmds(&data->cmd);
	if (data->redirections)
	{
		free(data->redirections);
		data->redirections = NULL;
	}
	ft_free_exec(data);
	data->nb_of_cmds = 0;
}
