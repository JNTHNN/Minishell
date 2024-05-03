/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:30:58 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 17:48:33 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_strncmp(cmd->args[i], data->env[j],
					ft_strlen(cmd->args[i])) == 0)
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
