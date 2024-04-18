/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:21:25 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/18 10:57:51 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tokens(t_tok_lst **tokens)
{
	t_tok_lst	*current;

	if (!*tokens)
		return ;
	while (*tokens)
	{
		current = *tokens;
		if (current->token != NULL)
		{
			free(current->token);
			current->token = NULL;
		}
		*tokens = current->next;
		free(current);
	}
	*tokens = NULL;
}

void	ft_free_redirections(t_redir_lst **lst)
{
	t_redir_lst	*current;

	if (!*lst)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		free((*lst)->filename);
		free(*lst);
		*lst = current;
	}
	*lst = NULL;
}

void	ft_free_cmds(t_cmd **cmd)
{
	t_cmd	*current;

	if (!*cmd)
		return ;
	while (*cmd)
	{
		current = (*cmd)->right;
		free((*cmd)->args);
		(*cmd)->args = NULL;
		ft_free_redirections(&(*cmd)->redirections);
		free(*cmd);
		*cmd = current;
	}
	*cmd = NULL;
}

void	ft_free_data(t_data *data)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		if (data->hist)
		{
			if (data->hist->newline)
			{
				free(data->hist->newline);
				data->hist->newline = NULL;
			}
			if (data->hist->lastline)
			{
				free(data->hist->lastline);
				data->hist->lastline = NULL;
			}
			free(data->hist);
			data->hist = NULL;
		}
		free_arr(data->env);
		if (data->tokens)
			ft_free_tokens(&data->tokens);
		if (data->cmd)
			ft_free_cmds(&data->cmd);
		if (data->redirections)
		{
			free(data->redirections);
			data->redirections = NULL;
		}
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
	data->nb_of_cmds = 0;
}
