/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:30:54 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:36:02 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns the size of the token list.
*/
static int	ft_tok_lstsize(t_tok_lst *lst)
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
** Adds a new token node to the end of the token list.
*/
static void	ft_tok_lstadd_back(t_tok_lst **lst, t_tok_lst *new)
{
	t_tok_lst	*last;

	if (!lst || !new)
		return ;
	if (ft_tok_lstsize(*lst))
	{
		last = ft_tok_lstlast(*lst);
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
** Creates a new token node with the given string, id, and type.
*/
static t_tok_lst	*ft_create_new_tok(char *str, int id, t_tok_type type)
{
	t_tok_lst	*new_node;

	new_node = (t_tok_lst *)malloc(sizeof(t_tok_lst));
	if (!new_node)
		return (NULL);
	new_node->id = id;
	new_node->token = str;
	new_node->r_type = ft_find_redir_type(str, type);
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/*
** Returns the last node in the token list.
*/
t_tok_lst	*ft_tok_lstlast(t_tok_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*
** Adds a new token node to the token list.
*/
int	ft_add_tok_node(char *str, int id, t_tok_type type, t_data *data)
{
	t_tok_lst	*node;

	node = ft_create_new_tok(str, id, type);
	if (!node)
		return (EXIT_FAILURE);
	ft_tok_lstadd_back(&data->tokens, node);
	return (EXIT_SUCCESS);
}
