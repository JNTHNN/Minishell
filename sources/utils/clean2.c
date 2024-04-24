/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:29:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/24 14:27:28 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	}
}

void	ft_free_exec(t_data *data)
{
	t_exec	*exec;

	exec = data->exec;
	if (data && exec)
	{
		if (exec->pipe_fd[0] != -1)
			close(exec->pipe_fd[0]);
		if (exec->pipe_fd[1] != -1)
			close(exec->pipe_fd[1]);
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
