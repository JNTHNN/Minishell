/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:14:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/24 11:58:45 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	checker for cd ~ | return 0 if error
*/
int	ft_check_tilde(t_cd *cd)
{
	if (!cd->home)
		return (ft_errno(ERR_HOME, EXEC_FAIL, cd->data), 0);
	cd->temp_tilde = ft_strjoin(cd->home + 5, cd->dir + 1);
	if (chdir(cd->temp_tilde) == -1)
	{
		cd->data->err_info = ft_strjoin("cd: ", cd->temp_tilde);
		return (ft_errno(cd->data->err_info, EXEC_FAIL, cd->data), 0);
	}
	return (1);
}

/*
**	checker for cd | return 0 if error
*/
int	ft_check_home(t_cd *cd)
{
	if (!cd->home)
		return (ft_errno(ERR_HOME, EXEC_FAIL, cd->data), 0);
	if (chdir(cd->home + 5) == -1)
	{
		cd->data->err_info = ft_strjoin("cd: ", cd->home + 5);
		return (ft_errno(cd->data->err_info, EXEC_FAIL, cd->data), 0);
	}
	return (1);
}

/*
**	checker for cd - | return 0 if error
*/
int	ft_check_minus(t_cd *cd)
{
	if (!cd->oldpwd)
		return (ft_errno(ERR_OLDPWD, EXEC_FAIL, cd->data), 0);
	if (chdir(cd->oldpwd + 7) == -1)
	{
		cd->data->err_info = ft_strjoin("cd: ", cd->oldpwd + 7);
		return (ft_errno(cd->data->err_info, EXEC_FAIL, cd->data), 0);
	}
	printf("%s\n", cd->oldpwd + 7);
	cd->temp_minus = ft_strdup(cd->oldpwd + 7);
	return (1);
}
