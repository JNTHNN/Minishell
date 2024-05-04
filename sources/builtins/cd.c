/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 23:43:22 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	change pwd in env according to path type (without arg; absolute; relative)
*/
static void	ft_change_pwd(t_cd *cd)
{
	if (!cd->dir)
		ft_cd_home(cd);
	else if (cd->dir[0] == '/')
		ft_cd_absolute(cd);
	else
		ft_cd_relative(cd);
}

/*
**	check arg after cd ( - ; ~ ; path)
*/
static int	ft_check_dir(t_cd *cd)
{
	int		rv;

	rv = 0;
	if (cd->dir)
	{
		if (!ft_strncmp(cd->dir, MINUS, 1))
			return (rv = ft_check_minus(cd));
		if (!ft_strncmp(cd->dir, TILDE, 1))
			rv = ft_check_tilde(cd);
		else if (!chdir(cd->dir))
			rv = 1;
		else
			ft_errno(cd->dir, 1, cd->data, false);
	}
	if (!cd->dir)
		rv = ft_check_home(cd);
	return (rv);
}

/*
**	initialize the cd struct
*/
t_cd	*ft_init_cd(t_data *data, t_cmd *cmd)
{
	t_cd		*cd;
	static char	cwd[PATH_MAX];

	cd = (t_cd *)malloc(sizeof(t_cd));
	cd->data = data;
	cd->cmd = cmd;
	cd->dir = cmd->args[1];
	cd->pwd = getcwd(cwd, sizeof(cwd));
	if (!cd->pwd)
		ft_errno("cd", 1, data, false);
	cd->oldpwd = ft_getenv(data, OLDPWD);
	cd->home = ft_getenv(data, HOME);
	cd->err = NULL;
	cd->temp_tilde = NULL;
	cd->temp_pwd = NULL;
	cd->temp_path = NULL;
	return (cd);
}

/*
**	clean all the cd struct
*/
static void	ft_free_cd(t_cd *cd)
{
	if (cd->err)
		free(cd->err);
	if (cd->temp_tilde)
		free(cd->temp_tilde);
	// if (cd->temp_pwd)
	// 	ft_free_array(cd->temp_pwd); // EXPLOSION -> clear 1 trop loin
	if (cd->temp_path)
		ft_free_array(cd->temp_path);
	free(cd);
}

/*
**	if the direction works -> we change pwd + oldpwd
*/
void	ft_cd(t_data *data, t_cmd *cmd)
{
	t_cd	*cd;

	cd = ft_init_cd(data, cmd);
	if (ft_check_dir(cd))
		ft_change_pwd(cd);
	ft_free_cd(cd);
}
