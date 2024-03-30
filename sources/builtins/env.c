/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:20:22 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/30 16:28:30 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
