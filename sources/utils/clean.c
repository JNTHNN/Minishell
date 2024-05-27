/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:21:25 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 11:52:06 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free memory allocated for the redirections linked list.
*/
static void	ft_free_redirections(t_redir_lst **lst)
{
	t_redir_lst	*current;

	if (!*lst)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		free((*lst)->filename);
		free((*lst)->hd_path);
		free(*lst);
		*lst = current;
	}
	*lst = NULL;
}

/*
** Free memory allocated for the local history (with !! command).
*/
static void	ft_free_hist(t_hist *hist)
{
	if (hist->newline)
	{
		free(hist->newline);
		hist->newline = NULL;
	}
	if (hist->lastline)
	{
		free(hist->lastline);
		hist->lastline = NULL;
	}
	free(hist);
	hist = NULL;
}

/*
** Free memory allocated for the tokens linked list used in the lexer.
*/
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

/*
** Free memory allocated for the commands linked list.
*/
void	ft_free_cmds(t_cmd **cmd)
{
	t_cmd	*current;

	if (!*cmd)
		return ;
	while (*cmd)
	{
		current = (*cmd)->right;
		ft_free_array((*cmd)->args);
		ft_free_redirections(&(*cmd)->redirections);
		free(*cmd);
		*cmd = current;
	}
	*cmd = NULL;
}

/*
** Free all memory allocated in the data structure.
*/
void	ft_free_data(t_data *data)
{
	if (data)
	{
		if (data->input)
		{
			free(data->input);
			data->input = NULL;
		}
		if (data->hist)
			ft_free_hist(data->hist);
		ft_free_array(data->env);
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
