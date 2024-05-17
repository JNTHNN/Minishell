/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:33:05 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/17 19:15:02 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	free the env list
*/
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

/*
**	measures the size of the env list
*/
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

/*
**	converts env list to **tab
*/
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

/*
**	replaces the old env with the new
*/
void	ft_update_env(t_env *head, t_data *data)
{
	ft_free_array(data->env);
	data->env = ft_ltoa(head);
	ft_free_lst(head);
}
