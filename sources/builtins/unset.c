/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:30:58 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/22 18:05:02 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_var(char *str, t_data *data)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_var(str);
	if (!var || ft_isdigit(var[i]))
		return (free(var), data->err_info = str,
			ft_print_unset_error(ERR_UNSET_VAR_ID, data), false);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) || var[i] == '=' || !var[0])
			return (free(var), data->err_info = str,
				ft_print_unset_error(ERR_UNSET_VAR_ID, data), false);
		i++;
	}
	return (free(var), true);
}

void	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->args[++i])
	{
		j = -1;
		while (data->env[++j])
		{
			if (!ft_check_var(cmd->args[i], data))
				break ;
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
		}
	}
}
