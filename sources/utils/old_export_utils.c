/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:26:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 15:49:20 by jgasparo         ###   ########.fr       */
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

static void	ft_add_env(t_env **head, char *var)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->var = var;
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
		node->var = ft_strdup(var);
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
	char	*equal_sign;

	current = *head;
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		while (current)
		{
			if (!ft_strncmp(current->var, var, ft_strlen(var)))
			{
				free(current->var);
				current->var = ft_strdup(var);
				*equal_sign = '=';
				return ;
			}
			current = current->next;
		}
		*equal_sign = '=';
	}
	ft_add_env(head, var);
}
