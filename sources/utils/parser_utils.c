/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:59:27 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/20 22:26:01 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok_lst	*ft_tok_lstback(t_tok_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL || lst->prev->token != PIPE)
		lst = lst->prev;
	return (lst);
}
