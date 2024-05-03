/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:14:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 13:03:32 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	checker for cd ~ | return 0 if error
*/
int	ft_check_tilde(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME=");
	if (!home)
	{
		ft_putstr_fd(ERR_HOME, 2);
		ft_errno(NULL, 1, data, false);
		return (0);
	}
	if (chdir(ft_strjoin(home + 5, data->cmd->args[1] + 1)) == -1)
	{
		ft_errno("cd", 1, data, false);
		return (0);
	}
	return (1);
}

/*
**	checker for cd | return 0 if error
*/
int	ft_check_home(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME=");
	if (!home)
	{
		ft_putstr_fd(ERR_HOME, 2);
		ft_errno(NULL, 1, data, false);
		return (0);
	}
	if (chdir(home + 5) == -1)
	{
		ft_errno("cd", 1, data, false);
		return (0);
	}
	return (1);
}

/*
**	checker for cd - | return 0 if error
*/
int	ft_check_minus(t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_getenv(data, "OLDPWD=");
	if (!oldpwd)
	{
		ft_putstr_fd(ERR_OLDPWD, 2);
		ft_errno(NULL, 1, data, false);
		return (0);
	}
	if (chdir(oldpwd + 7) == -1)
	{
		ft_errno("cd", 1, data, false);
		return (0);
	}
	return (1);
}
