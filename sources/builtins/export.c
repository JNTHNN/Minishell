/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/15 14:49:40 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_var(char *str, t_data *data)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_var(str);
	if (var[i] == '=')
		return (ft_errno(ERR_VAR_EQ, 1, data), 0);
	if (!var || ft_isdigit(var[i]))
		return (ft_errno(ERR_VAR_ID, 1, data), 0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]))
			return (ft_errno(ERR_VAR_EQ, 1, data), 0);
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_env	*head;
	int		i;

	head = ft_setup_env(data->env);
	if (!head)
		ft_errno(ERR_MEM, 2, data);
	i = 1;
	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], "export", 6))
		{
			if (cmd->args[i])
			{
				while (cmd->args[i])
				{
					if (ft_check_var(cmd->args[i], data))
						ft_modify_or_add_env(&head, cmd->args[i], data);
					i++;
				}
			}
			else
				ft_print_env(head);
		}
	}
	return (ft_update_env(head, data), EXIT_SUCCESS);
}
