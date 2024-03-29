/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:21:25 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/29 22:27:50 by gdelvign         ###   ########.fr       */
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
		current = (*tokens)->next;
		free(*tokens);
		*tokens = current;
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
		free_arr((*cmd)->args);
		(*cmd)->args = NULL;
		ft_free_redirections(&(*cmd)->redirections);
		*cmd = current;
	}
	*cmd = NULL;
}

void	ft_reset_data(t_data *data)
{
	ft_free_cmds(&data->cmd);
}
