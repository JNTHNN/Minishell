/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 21:55:39 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	export sans aucune option a l'execution va print "declare -x" par variable
**	de l'env triée par ordre ascii ? 
**	export avec un nom de variable va l'ajouter aux variables d'env sans print
**	The export and declare -x commands allow parameters and functions to be 
**	added to and deleted from the environment.
**	export test1 : test1 n'est pas herite dans l'env mais visible avec export
**	export test1= : test1 est herite dans l'env avec la valeur qui suit = / donc 
**	visible dans env.
**	declare -x rajoute des "" pour le contenu de la variable
*/

#include "../../includes/minishell.h"

void	ft_free_lst(t_env *head)
{
	t_env *next_node;

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

char	**ft_ltoa(t_env *head)
{
	t_env	*temp;
	int		i;
	int		count;
	char	**new_env;

	i = 0;
	temp = head;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
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
	// ft_free_array(data->env);
	data->env = ft_ltoa(head);
	ft_free_lst(head);
	// ft_env(data);
}

void	ft_export(t_data *data)
{
	t_env	*head;

	head = ft_setup_env(data->env);
	if (data->cmd->args)
	{
		if (!ft_strncmp(data->cmd->args[0], "export", 6))
		{
			if (data->cmd->args[1])
			{
				ft_modify_or_add_env(&head,
					data->cmd->args[1]);
				// ft_show_list(head);
			}
			else
			{
				ft_print_env(head);
			}
		}
	}
	ft_update_env(head, data);
}
