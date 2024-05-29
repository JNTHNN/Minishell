/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/29 10:42:56 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if the env var nam is valid | return false if not
*/
static bool	ft_check_var(char *str, t_data *data)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_var(str);
	printf("VAR %s\n", var);
	if (var[i] == '=')
		return (free(var), ft_errno(ERR_VAR_EQ, EXEC_FAIL, data), false);
	if (!var || ft_isdigit(var[i]))
		return (free(var), ft_errno(ERR_VAR_ID, EXEC_FAIL, data), false);
	while (var[i])
	{
		if (!ft_is_valid_var_name(var[i]))
			return (free(var), ft_errno(ERR_VAR_EQ, EXEC_FAIL, data), false);
		i++;
	}
	return (free(var), true);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_env	*head;
	int		i;

	head = ft_setup_env(data->env);
	if (!head)
		return (ft_errno(ERR_MEM, EX_MISCERROR, data), EXEC_FAIL);
	i = 1;
	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], EXPORT, 6))
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
