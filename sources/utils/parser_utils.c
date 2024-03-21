/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:59:27 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/21 16:16:13 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_cmd	*ft_create_new_cmd(char *str, int id, t_tok_type type)
// {
// 	t_cmd	*new_node;

// 	new_node = (t_cmd *)malloc(sizeof(t_cmd));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->id = id;
// 	new_node->token = str;
// 	new_node->type = type;
// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	return (new_node);
// }

t_tok_lst	*ft_tok_lstback(t_tok_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL || lst->prev->token[0] != PIPE)
		lst = lst->prev;
	return (lst);
}
