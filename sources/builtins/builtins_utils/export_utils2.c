/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:27:48 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/03 12:37:13 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  Print env (via export) in ascii sort
*/

/*
**	Swap nodes a to b
*/
static void	ft_swap_nodes(t_env *a, t_env *b)
{
	char	*temp_var;
	char	*temp_data;

	temp_var = a->var;
	a->var = b->var;
	b->var = temp_var;
	temp_data = a->data;
	a->data = b->data;
	b->data = temp_data;
}

/*
**	Sorts env list nodes in ascending order ascii
*/
static void	ft_sort_env(t_env *head)
{
	int		swapped;
	t_env	*unsort;
	t_env	*sorted;

	swapped = 1;
	sorted = NULL;
	if (head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		unsort = head;
		while (unsort->next != sorted)
		{
			if (ft_strncmp(unsort->var, unsort->next->var,
					ft_strlen(unsort->var)) > 0)
			{
				ft_swap_nodes(unsort, unsort->next);
				swapped = 1;
			}
			unsort = unsort->next;
		}
	}
	sorted = unsort;
}

/*
**	Reset/free name and data if exists + reassign at NULL
*/
void	ft_reset_env_var(char *name, char *data)
{
	if (name)
	{
		free(name);
		name = NULL;
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
}

/*
**	Print env from export
*/
void	ft_print_env(t_env *head)
{
	t_env	*node;

	ft_sort_env(head);
	node = head;
	while (node)
	{
		if (node->var && node->data)
		{
			if (!ft_strncmp(node->var, "_=", 2))
				node = node->next;
			printf("declare -x %s\"%s\"\n", node->var, node->data);
		}
		node = node->next;
	}
	node = head;
	while (node)
	{
		if (node->var && !node->data)
			printf("declare -x %s\n", node->var);
		node = node->next;
	}
}
