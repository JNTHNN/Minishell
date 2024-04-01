/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:12:21 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/02 00:43:51 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

bool	ft_is_builtin(char *name)
{
	int			i;
	static char	*builtin_tab[8] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};

	i = 0;
	if (name)
	{
		while (builtin_tab[i])
		{
			if (!ft_strncmp(name, builtin_tab[i], ft_strlen(name)))
				return (true);
			i++;
		}
	}
	if (name)
	{
		while (builtin_tab[i])
		{
			if (!ft_strncmp(name, builtin_tab[i], ft_strlen(name)))
				return (true);
			i++;
		}
	}
	return (false);
}

void	ft_builtin(t_data *data)
{
	if (!ft_strncmp(data->cmd->args[0], "echo", 4))
		ft_echo(data);
	if (!ft_strncmp(data->cmd->args[0], "cd", 2))
		ft_cd(data);
	if (!ft_strncmp(data->cmd->args[0], "pwd", 3))
		ft_pwd(data);
	if (!ft_strncmp(data->cmd->args[0], "export", 6))
		ft_export(data);
	if (!ft_strncmp(data->cmd->args[0], "unset", 5))
		ft_unset(data) ;
	if (!ft_strncmp(data->cmd->args[0], "env", 3))
		ft_env(data);
	if (!ft_strncmp(data->cmd->args[0], "exit", 4))
		ft_exit(data);
}
