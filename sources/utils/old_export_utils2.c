/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:27:48 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 15:49:43 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Print env (via export) in ascii sort
*/

static void	ft_swap_nodes(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->var;
	a->var = b->var;
	b->var = temp;
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
		sorted = unsort;
	}
}

void	ft_print_env(t_env *head)
{
	char	*equal_sign;

	ft_sort_env(head);
	while (head)
	{
		equal_sign = ft_strchr(head->var, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", head->var, equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("declare -x %s\n", head->var);
		head = head->next;
	}
}

void	ft_show_list(t_env *head)
{
	while (head)
	{
		printf("%s\n", head->var);
		head = head->next;
	}
}
