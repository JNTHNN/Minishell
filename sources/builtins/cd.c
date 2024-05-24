/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/24 12:00:02 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	clean all the cd struct
*/
static void	ft_free_cd(t_cd *cd)
{
	if (cd->temp_tilde)
	{
		free(cd->temp_tilde);
		cd->temp_tilde = NULL;
	}
	if (cd->temp_pwd)
		ft_free_array(cd->temp_pwd);
	if (cd->temp_path)
		ft_free_array(cd->temp_path);
	if (cd->new_pwd)
	{
		free(cd->new_pwd);
		cd->new_pwd = NULL;
	}
	if (cd->temp_minus)
	{
		free(cd->temp_minus);
		cd->temp_minus = NULL;
	}
	free(cd);
}

/*
**	change pwd in env according to path type (without arg; absolute; relative)
*/
static int	ft_change_pwd(t_cd *cd)
{
	if (!cd->dir)
		ft_cd_home(cd);
	else if (cd->dir[0] == '/' || cd->temp_tilde
		|| cd->temp_minus || (cd->pwd && !ft_getenv(cd->data, PWD)))
		ft_cd_absolute(cd);
	else
	{
		if (!cd->pwd)
			return (ft_free_cd(cd),
				ft_handle_error(cd->data, E_CWD), EXEC_FAIL);
		else
			ft_cd_relative(cd);
	}
	return (EXIT_SUCCESS);
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
			ft_errno(cd->dir, EXEC_FAIL, cd->data);
	}
	if (!cd->dir)
		rv = ft_check_home(cd);
	return (rv);
}

/*
**	initialize the cd struct
*/
static t_cd	*ft_init_cd(t_data *data, t_cmd *cmd)
{
	t_cd			*cd;
	static char		cwd[PATH_MAX];

	cd = (t_cd *)malloc(sizeof(t_cd));
	if (!cd)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	cd->data = data;
	cd->cmd = cmd;
	cd->dir = cmd->args[1];
	cd->pwd = NULL;
	if (getcwd(cwd, PATH_MAX))
		cd->pwd = cwd;
	cd->oldpwd = ft_getenv(data, OLDPWD);
	cd->home = ft_getenv(data, HOME);
	cd->temp_tilde = NULL;
	cd->temp_minus = NULL;
	cd->temp_pwd = NULL;
	cd->temp_path = NULL;
	cd->new_pwd = NULL;
	cd->temp = NULL;
	return (cd);
}

/*
**	if the direction works -> we change pwd + oldpwd
*/
void	ft_cd(t_data *data, t_cmd *cmd)
{
	t_cd	*cd;

	cd = ft_init_cd(data, cmd);
	if (ft_check_dir(cd))
	{
		if (ft_change_pwd(cd))
			return ;
	}
	ft_free_cd(cd);
}
