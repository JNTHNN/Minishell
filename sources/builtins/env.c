/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:20:22 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/28 15:19:52 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
	{
		if (data->env)
		{
			if (!data->env[i])
				return ;
			while (data->env[i])
			{
				if (ft_strchr(data->env[i], 61))
					printf("%s\n", data->env[i]);
				i++;
			}
		}
	}
	else
	{
		data->err_info = cmd->args[1];
		ft_handle_error(data, E_ENV);
	}
}
