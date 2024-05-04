/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:14:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 23:51:38 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	checker for cd ~ | return 0 if error
*/
int	ft_check_tilde(t_cd *cd)
{
	cd->temp_tilde = ft_strjoin(cd->home + 5, cd->dir + 1);
	if (!cd->home)
		return (ft_errno(ERR_HOME, 1, cd->data, false), 0);
	if (chdir(cd->temp_tilde) == -1)
	{
		cd->err = ft_strjoin("cd: ", cd->temp_tilde);
		return (ft_errno(cd->err, 1, cd->data, false), 0);
	}
	return (1);
}

/*
**	checker for cd | return 0 if error
*/
int	ft_check_home(t_cd *cd)
{
	if (!cd->home)
		return (ft_errno(ERR_HOME, 1, cd->data, false), 0);
	if (chdir(cd->home + 5) == -1)
	{
		cd->err = ft_strjoin("cd: ", cd->home + 5);
		return (ft_errno(cd->err, 1, cd->data, false), 0);
	}
	return (1);
}

/*
**	checker for cd - | return 0 if error
*/
int	ft_check_minus(t_cd *cd)
{
	if (!cd->oldpwd)
		return (ft_errno(ERR_OLDPWD, 1, cd->data, false), 0);
	if (chdir(cd->oldpwd + 7) == -1)
	{
		cd->err = ft_strjoin("cd: ", cd->oldpwd + 7);
		return (ft_errno(cd->err, 1, cd->data, false), 0);
	}
	return (1);
}
