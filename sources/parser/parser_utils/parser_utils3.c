/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:48:48 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/15 15:49:57 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts how many pipes are present in the token list.
*/
int	ft_count_pipes(t_tok_lst *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (lst->type == OPERATOR && lst->r_type == R_PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}

/*
** Frees and sets the token value to NULL
** for the current and next nodes in a token list.
** It "nullifies" redirection token nodes to avoid them to be considered
** as command arguments.
*/
void	ft_nullify_tok_nodes(t_tok_lst *node)
{
	t_tok_lst	*next;

	next = node->next;
	if (next && next->token)
	{
		free(next->token);
		next->token = NULL;
	}
	if (node && node->token)
	{
		free(node->token);
		node->token = NULL;
	}
}

/*
** Checks if token is an redirection operator and launch the nullification.
*/
void	ft_remove_redir(t_tok_lst *lst)
{
	t_tok_lst	*current;
	t_tok_lst	*tmp;

	current = lst;
	while (current)
	{
		tmp = current->next;
		if (current->type == OPERATOR && current->r_type != R_PIPE)
		{
			tmp = current->next->next;
			ft_nullify_tok_nodes(current);
		}
		current = tmp;
	}
}

/*
** Initializes an array of redirections (lined lists) and set each to NULL.
*/
int	ft_init_redir(t_redir_lst ***redirections, t_data **data, int *cmd_nb)
{
	int	i;

	*cmd_nb = ft_count_pipes((*data)->tokens) + 1;
	*redirections = (t_redir_lst **)malloc(*cmd_nb * sizeof(t_redir_lst *));
	if (!*redirections)
		return (E_MEM);
	(*data)->redirections = *redirections;
	i = -1;
	while (++i < *cmd_nb)
		(*redirections)[i] = NULL;
	return (EXIT_SUCCESS);
}

/*
** Counts the number of tokens between the current node and the next pipe
** or the end of the list.
*/
int	ft_count_cmd_args(t_tok_lst **current)
{
	int	arg_count;

	arg_count = 0;
	while (*current && (*current)->r_type != R_PIPE)
	{
		if ((*current)->token)
			arg_count++;
		*current = (*current)->next;
	}
	return (arg_count);
}
