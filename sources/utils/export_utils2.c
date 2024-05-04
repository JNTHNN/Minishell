/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:27:48 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 22:45:42 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Print env (via export) in ascii sort
*/

/*
**	swap nodes a to b
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
**	sorts env list nodes in ascending order ascii
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
**	print env from export
*/
void	ft_print_env(t_env *head)
{
	t_env	*node;

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
