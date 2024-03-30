/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/30 19:32:42 by jgasparo         ###   ########.fr       */
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

	head = ft_setup_env(data->env);
	if (data->cmd->args)
	{
		if (!ft_strncmp(data->cmd->args[0], "export", 6))
		{
			if (data->cmd->args[1])
			{
				ft_modify_or_add_env(&head,
					data->cmd->args[1]);
				ft_show_list(head);
			}
			else
			{
				ft_print_env(head);
			}
		}
	}
}
