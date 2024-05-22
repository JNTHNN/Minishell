/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:59:27 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/17 21:05:08 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	if (lst)
	{
		while (lst != NULL)
		{
			lst = lst->right;
			size++;
		}
	}
	return (size);
}

t_cmd	*ft_cmd_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->right != NULL)
		lst = lst->right;
	return (lst);
}

void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst || !new)
		return ;
	if (ft_cmd_lstsize(*lst))
	{
		last = ft_cmd_lstlast(*lst);
		last->right = new;
		new->left = last;
	}
	else
	{
		*lst = new;
		new->right = NULL;
	}
}

t_cmd	*ft_create_new_cmd(char ***args, t_data *data, int id)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->id = id;
	if (!**args)
	{
		new_node->args = NULL;
		new_node->is_builtin = false;
	}
	else
	{
		new_node->args = *args;
		new_node->is_builtin = ft_is_builtin(new_node->args[0]);
	}
	new_node->redirections = data->redirections[id - 1];
	ft_add_redir_node_id(&new_node->redirections);
	new_node->data = data;
	new_node->expanded_char = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	ft_add_cmd_node(char ***args, t_data *data, int id)
{
	t_cmd	*node;

	node = ft_create_new_cmd(args, data, id);
	if (!node)
		return (EXIT_FAILURE);
	ft_cmd_lstadd_back(&data->cmd, node);
	return (EXIT_SUCCESS);
}
