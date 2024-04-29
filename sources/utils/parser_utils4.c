/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:25:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/29 10:38:54 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_redir_node_id(t_redir_lst **redirections)
{
	int			i;
	t_redir_lst	*current;

	current = *redirections;
	if (current)
	{
		i = 0;
		while (current != NULL)
		{
			current->id = ++i;
			current = current->next;
		}
	}
}
