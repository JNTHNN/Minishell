/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:12:21 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/22 17:17:18 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** checker for builtin | return true if it's a builtin
*/
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
	return (false);
}

/*
**	launch the right builtin
*/
int	ft_builtin(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		ft_echo(data, cmd);
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		ft_cd(data, cmd);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		ft_pwd(data);
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		ft_export(data, cmd);
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		ft_unset(data, cmd);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		ft_env(data, cmd);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		ft_exit(data, cmd);
	return (EXIT_FAILURE);
}
