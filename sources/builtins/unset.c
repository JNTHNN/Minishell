/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:30:58 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/31 16:13:37 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if the env var nam is valid | return false if not
*/
static int	ft_check_var(char *str, t_data *data)
{
	int		i;
	char	*var;
	char	*check_var;

	i = 0;
	var = ft_strdup(str);
	check_var = ft_strjoin(var, EQUAL);
	if (!var || !var[0] || ft_isdigit(var[i]) || var[i] == '=')
		return (free(check_var), free(var), data->err_info = str,
			ft_print_unset_error(ERR_UNSET_VAR_ID, data), false);
	while (var[i])
	{
		if (!ft_is_valid_var_name(var[i]) || var[i] == '=' || !var[0])
			return (free(check_var), free(var), data->err_info = str,
				ft_print_unset_error(ERR_UNSET_VAR_ID, data), false);
		i++;
	}
	if (!ft_getenv(data, check_var))
		return (free(check_var), free(var), false);
	return (free(check_var), free(var), true);
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
			if (!ft_strncmp(cmd->args[i], data->env[j],
					ft_strlen(cmd->args[i])))
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
