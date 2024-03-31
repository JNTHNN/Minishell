/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/31 16:22:46 by jgasparo         ###   ########.fr       */
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

void	ft_export(t_data *data)
{
	t_env	*head;
	// char	*deb;
	// char	*fin;

	head = ft_setup_env(data->env);	//creation de la liste chainee a base du tab env
	// ft_show_list(head);
	if (data->cmd->args)
	{
		if (!ft_strncmp(data->cmd->args[0], "export", 6)) // on recheck si c'est "export"
		{
			if (data->cmd->args[1]) // si c'est "export var=data"
			{
					// deb = ft_var(data->cmd->args[1]);
					// fin = ft_data(data->cmd->args[1]);
					// printf("TEST DEB[%s]\n", deb);
					// printf("TEST FIN[%s]\n", fin);
				ft_modify_or_add_env(&head, // modifie ou ajoute
					data->cmd->args[1]);
				ft_show_list(head); // print de la liste chainee
			}
			else // sinon cest juste "export"
			{
				ft_print_env(head);
			}
		}
	}
}
// void free_array(char **array)
// {
// 	int i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// void update_env(t_data *data, t_env *head)
// {
// 	// Libérer l'ancien tableau
// 	free_array(data->env);

// 	// Convertir la liste chaînée en un nouveau tableau
// 	data->env = list_to_array(head);
// }

// char **list_to_array(t_env *head)
// {
// 	t_env *tmp = head;
// 	int count = 0;
// 	while (tmp)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}

// 	char **array = malloc((count + 1) * sizeof(char *));
// 	if (!array)
// 		return NULL;

// 	tmp = head;
// 	for (int i = 0; i < count; i++)
// 	{
// 		array[i] = strdup(tmp->var); // Assurez-vous que tmp->var est une chaîne de caractères
// 		tmp = tmp->next;
// 	}
// 	array[count] = NULL;

// 	return array;
// }
