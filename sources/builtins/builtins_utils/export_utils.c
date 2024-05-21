/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:26:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/21 16:22:01 by jgasparo         ###   ########.fr       */
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
**	add the new node with var + data in env list
*/
static int	ft_add_env(t_env **head, char *var, char *data)
{
	t_env	*new_node;

	new_node = ft_new_node(var, data);
	ft_envadd_back(head, new_node);
	return (EXIT_SUCCESS);
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

/*
**	Check if var env already exist then modify
**	or just add
*/
void	ft_modify_or_add_env(t_env **head, char *var, t_data *d)
{
	t_env	*current;
	char	*name;
	char	*data;
	int		ret;

	name = ft_var(var);
	data = ft_data(var);
	current = *head;
	if (data)
	{
		while (current)
		{
			if (!ft_strncmp(current->var, name, ft_strlen(name)))
			{
				free(name);
				free(current->data);
				current->data = ft_strdup(data);
				free(data);
				return ;
			}
			current = current->next;
		}
	}
	ret = ft_add_env(head, name, data);
	free(name);
	name = NULL;
	free(data);
	data = NULL;
	if (ret)
		ft_errno(ERR_MEM, EX_MISCERROR, d);
}
