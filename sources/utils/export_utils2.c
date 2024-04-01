/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:27:48 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/01 15:24:03 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Print env (via export) in ascii sort
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

void	ft_print_env(t_env *head)
{
	t_env *node;

	ft_sort_env(head);
	node = head;
	while (node)
	{
		if (node->var && node->data)
			printf("declare -x %s\"%s\"\n", node->var, node->data);
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

void	ft_show_list(t_env *head)
{
	while (head)
	{
		if (head->var && head->data)
			printf("%s%s\n", head->var, head->data);
		else if (head->var && !head->data)
			printf("%s\n", head->var);

		head = head->next;
	}
}
