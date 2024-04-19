/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 22:34:34 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(t_data *data, t_cmd *cmd)
{
	t_env	*head;
	int		i;

	head = ft_setup_env(data->env);
	i = 1;
	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], "export", 6))
		{
			if (cmd->args[i])
			{
				while (cmd->args[i])
				{
					ft_modify_or_add_env(&head,
						cmd->args[i]);
					i++;
				}
			}
			else
				ft_print_env(head);
		}
	}
	ft_update_env(head, data);
}
