/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/04 03:15:55 by jgasparo         ###   ########.fr       */
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

void	ft_free_array(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

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
	int		i;

	head = ft_setup_env(data->env);	//creation de la liste chainee a base du tab env
	i = 1;
	if (data->cmd->args)
	{
		if (!ft_strncmp(data->cmd->args[0], "export", 6)) // on recheck si c'est "export"
		{
			if (data->cmd->args[i])
			{
				while (data->cmd->args[i])
				{
					if (data->cmd->args[i]) // si c'est "export var=data" 
					{
						ft_modify_or_add_env(&head, // modifie ou ajoute
							data->cmd->args[i]);
						// ft_show_list(head); // print de la liste chainee
					}
				i++;
				}
			}
			else // sinon cest juste "export"
			{
				ft_print_env(head);
			}
		}
	}
	ft_update_env(head, data);
}
		// maintenant que les modifs ont été faites, je dois retourner la liste chainee 
		// en char ** -> donc free l'ancien et le remplacer par le nouveau
		// free au passage la liste chainee aussi

//	GERER NOM DE VAR : ALPHANUM MAIS PEUT PAS COMMENCER PAR UN CHIFFRE + UNDERSCORE
// ERROR : export: `%ddd': not a valid identifier

// DOIT s'arreter au 1er = et prendre les autres en data