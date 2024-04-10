/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:14:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/10 19:17:58 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_tilde(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME=");
	if (!home)
	{
		perror("No HOME, No party");
		return (0);
	}
	if (chdir(ft_strjoin(home + 5, data->cmd->args[1] + 1)) == -1)
	{
		perror("cd tilde");
		return (0);
	}
	return (1);
}

int	ft_check_home(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME=");
	if (!home)
	{
		perror("No HOME, No party");
		return (0);
	}
	if (chdir(home + 5) == -1)
	{
		perror("cd home");
		return (0);
	}
	return (1);
}

int	ft_check_minus(t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_getenv(data, "OLDPWD=");
	if (!oldpwd)
	{
		perror("No OLDPWD, No party");
		return (0);
	}
	if (chdir(oldpwd + 7) == -1)
	{
		perror("cd minus");
		return (0);
	}
	return (1);
}
