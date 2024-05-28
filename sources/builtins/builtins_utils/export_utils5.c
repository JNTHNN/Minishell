/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:15:00 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/28 18:21:32 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
**	create new node for env list
*/
static t_env	*ft_new_node(char *var, char *data)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (node)
	{
		node->var = ft_var(var);
		if (data)
			node->data = ft_strdup(data);
		else
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
	t_env	*node[3];

	node[HEAD] = NULL;
	node[CURR] = NULL;
	if (!env || !*env)
		return (NULL);
	while (*env)
	{
		node[NEW] = ft_new_node(*env, NULL);
		if (!node[NEW])
			return (NULL);
		if (!node[HEAD])
		{
			node[HEAD] = node[NEW];
			node[CURR] = node[NEW];
		}
		else
		{
			node[CURR]->next = node[NEW];
			node[CURR] = node[NEW];
		}
		env++;
	}
	return (node[HEAD]);
}
