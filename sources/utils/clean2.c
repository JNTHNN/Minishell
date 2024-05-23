/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:29:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/15 14:59:13 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipes(t_data *data, t_exec *exec)
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
	free(exec->pipes);
	exec->pipes = NULL;
}

void	ft_free_exec(t_data *data)
{
	t_exec	*exec;

	if (data && data->exec)
	{
		exec = data->exec;
		if (exec && exec->pipes)
			ft_free_pipes(data, exec);
		if (exec && exec->child_pid)
		{
			free(exec->child_pid);
			exec->child_pid = NULL;
		}
		if (exec->fdin != NOT_INIT)
			close(exec->fdin);
		if (exec->fdout != NOT_INIT)
			close(exec->fdout);
		if (exec->tmpin != NOT_INIT)
			close(exec->tmpin);
		if (exec->tmpout != NOT_INIT)
			close(exec->tmpout);
		free(exec);
	}
}

void	ft_free_if_error(t_data *data)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		if (data->tokens)
			ft_free_tokens(&data->tokens);
		if (data->cmd)
			ft_free_cmds(&data->cmd);
		if (data->nb_of_cmds > 1)
			ft_free_exec(data);
	}
}

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
