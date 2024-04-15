/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:33:05 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 22:52:54 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_lst(t_env *head)
{
	t_env	*next_node;

	while (head)
	{
		next_node = head->next;
		if (head->var)
			free(head->var);
		else if (head->data)
			free(head->data);
		head = next_node;
	}
	head = NULL;
}

static int	ft_envsize(t_env *lst)
{
	int	size;

	size = 0;
	if (lst)
	{
		while (lst != NULL)
		{
			lst = lst->next;
			size++;
		}
	}
	return (size);
}

static char	**ft_ltoa(t_env *head)
{
	t_env	*temp;
	int		i;
	int		count;
	char	**new_env;

	i = 0;
	temp = head;
	count = ft_envsize(temp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	temp = head;
	while (i < count)
	{
		if (temp->data)
			new_env[i] = ft_strjoin(temp->var, temp->data);
		else
			new_env[i] = ft_strdup(temp->var);
		temp = temp->next;
		i++;
	}
	new_env[i] = NULL;
	ft_free_lst(temp);
	return (new_env);
}

void	ft_update_env(t_env *head, t_data *data)
{
	data->env = ft_ltoa(head);
	ft_free_lst(head);
}
