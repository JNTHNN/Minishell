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
}

void	ft_free_exec(t_data *data)
{
	t_exec	*exec;
	// int		i;

	exec = data->exec;
	if (data && exec)
	{
		// i = -1;
		// while (++i < data->nb_of_cmds - 1)
		// {
		// 	close(exec->pipes[i][0]);
		// 	close(exec->pipes[i][1]);
		// 	free(exec->pipes[i]);
		// 	exec->pipes[i] = NULL;
		// }
		ft_free_pipes(data, exec); // voir si c'est good
		free(exec->pipes);
		exec->pipes = NULL;
		if (exec->fdin != -1)
			close(exec->fdin);
		if (exec->fdout != -1)
			close(exec->fdout);
		if (exec->tmpin != -1)
			close(exec->tmpin);
		if (exec->tmpout)
			close(exec->tmpout);
	}
	free(exec);
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
		if (data->nb_of_cmds != 1)
			ft_free_exec(data);
	}
}