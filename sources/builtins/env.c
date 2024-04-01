/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:20:22 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/02 01:32:04 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GERER LES EXPORT SANS DATA

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		if (!data->env[i])
			return ;
		while (data->env[i])
			printf("%s\n", data->env[i++]);
	}
}
