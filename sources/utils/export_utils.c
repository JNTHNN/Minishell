/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:26:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 22:44:58 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Initialize env in linked list
*/

static void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (!lst)
		return ;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;
}

static void	ft_add_env(t_env **head, char *var, char *data)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->var = var;
	new_node->data = data;
	new_node->next = NULL;
	ft_envadd_back(head, new_node);
}

static t_env	*ft_new_node(char *var)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (node)
	{
		node->var = ft_var(var);
		node->data = ft_data(var);
		node->next = NULL;
	}
	return (node);
}

t_env	*ft_setup_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*node;

	head = NULL;
	current = NULL;
	if (!env || !*env)
		return (NULL);
	while (*env)
	{
		node = ft_new_node(*env);
		if (!head)
		{
			head = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = node;
		}
		env++;
	}
	return (head);
}

/*
**	Check if var env already exist then modify
**	or just add
*/

void	ft_modify_or_add_env(t_env **head, char *var)
{
	t_env	*current;
	char	*deb;
	char	*fin;

	deb = ft_var(var);
	fin = ft_data(var);
	current = *head;
	if (fin)
	{
		while (current)
		{
			if (!ft_strncmp(current->var, deb, ft_strlen(deb)))
			{
				free(current->data);
				current->data = ft_strdup(fin);
				return ;
			}
			current = current->next;
		}
	}
	ft_add_env(head, deb, fin);
}
