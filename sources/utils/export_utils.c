/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:26:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 20:09:20 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Initialize env in linked list
*/

/*
**	add env node to the end list
*/
static void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (!lst)
		return ;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;
}

/*
**	add the new node with var + data in env list
*/
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

/*
**	create new node for env list
*/
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

/*
**	create the env list from env tab
*/
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
	char	*name;
	char	*data;

	name = ft_var(var);
	data = ft_data(var);
	current = *head;
	if (data)
	{
		while (current)
		{
			if (!ft_strncmp(current->var, name, ft_strlen(name)))
			{
				free(current->data);
				current->data = ft_strdup(data);
				return ;
			}
			current = current->next;
		}
	}
	ft_add_env(head, name, data);
}
