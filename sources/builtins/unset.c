/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:30:58 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/04 03:05:26 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	unset sans rien ? ne se passe rien mais ne doit pas etre considerer comme
**	une erreur
**	unset avec un nom de variable presente dans l'env va la supprimer.
**	peut unset plusieurs var a la fois
*/

#include "../../includes/minishell.h"

void	ft_unset(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (data->cmd->args[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_strncmp(data->cmd->args[i], data->env[j],
				ft_strlen(data->cmd->args[i])) == 0)
			{
				free(data->env[j]);
				while (data->env[j])
				{
					data->env[j] = data->env[j + 1];
					j++;
				}
				break ;
			}
			j++;
		}
		i++;
	}
}
