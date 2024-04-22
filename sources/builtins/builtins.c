/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:12:21 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/21 01:40:43 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

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
	if (!ft_strncmp(cmd->args[0], "cd", 2))
		ft_cd(data, cmd);
	if (!ft_strncmp(cmd->args[0], "pwd", 3))
		ft_pwd(data);
	if (!ft_strncmp(cmd->args[0], "export", 6))
		ft_export(data, cmd);
	if (!ft_strncmp(cmd->args[0], "unset", 5))
		ft_unset(data, cmd);
	if (!ft_strncmp(cmd->args[0], "env", 3))
		ft_env(data);
	if (!ft_strncmp(cmd->args[0], "exit", 4))
		ft_exit(data);
	return (EXIT_SUCCESS);
}
