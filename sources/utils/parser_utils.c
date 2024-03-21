/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:59:27 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/21 21:03:08 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_create_new_cmd(char ***args)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = *args;
	new_node->redirections = NULL;
	new_node->ft_builtin = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tok_lst	*ft_tok_lstback(t_tok_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL || lst->prev->token[0] != PIPE)
		lst = lst->prev;
	return (lst);
}
