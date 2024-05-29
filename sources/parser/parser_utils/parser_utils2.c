/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:29:00 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/29 15:16:01 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns the size of the redir list.
*/
int	ft_redir_lstsize(t_redir_lst *lst)
{
	int	size;

	size = 0;
	if (lst)
	{
		while (lst != NULL)
		{
			lst = lst->next;
			size++;
		}
	}
	return (size);
}

/*
** Returns the last node in the redir list.
*/
t_redir_lst	*ft_redir_lstlast(t_redir_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*
** Adds a new redir node to the end of the redir list.
*/
void	ft_redir_lstadd_back(t_redir_lst **lst, t_redir_lst *new)
{
	t_redir_lst	*last;

	if (!lst || !new)
		return ;
	if (ft_redir_lstsize(*lst))
	{
		last = ft_redir_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}

/*
** Creates a new redir node with all its attributes.
*/
t_redir_lst	*ft_create_new_redir(t_tok_lst token, int cmd_nb)
{
	t_redir_lst	*new_node;

	new_node = (t_redir_lst *)malloc(sizeof(t_redir_lst));
	if (!new_node)
		return (NULL);
	new_node->r_type = token.r_type;
	new_node->filename = ft_strdup(token.next->token);
	new_node->hd_path = NULL;
	new_node->quoted = false;
	new_node->cmd_id = cmd_nb;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/*
** Adds a new redir node to the redir list.
*/
int	ft_add_redir_node(t_redir_lst **lst, t_tok_lst *token, int cmd_nb)
{
	t_redir_lst	*node;

	node = ft_create_new_redir(*token, cmd_nb);
	if (!node)
		return (EXIT_FAILURE);
	ft_redir_lstadd_back(lst, node);
	return (EXIT_SUCCESS);
}
