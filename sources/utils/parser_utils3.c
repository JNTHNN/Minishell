/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:48:48 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/28 10:25:11 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
