/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:30:58 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/17 20:24:17 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_var(str);
	if (!var || ft_isdigit(var[i]))
		return (ft_errno(ERR_U_VAR_ID, EXEC_FAIL, NULL), 0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) || var[i] == '=' || !var[0])
			return (ft_errno(ERR_U_VAR_EQ, EXEC_FAIL, NULL), 0);
		i++;
	}
	return (1);
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
			if (!ft_check_var(cmd->args[i]))
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
