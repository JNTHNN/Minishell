/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 15:37:03 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	change pwd in env according to path type (without arg; absolute; relative)
*/
static void	ft_change_pwd(t_data *data, t_cmd *cmd)
{
	char	*pwd;
	// static char	cwd[PATH_MAX];

	pwd = ft_getenv(data, "PWD");
	// if (!pwd)
	// {
	// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
	// 		pwd = cwd;
	// 	printf("start pwd = %s\n", cwd);
	// }
	if (!cmd->args[1])
		ft_cd_home(data, pwd);
	else if (cmd->args[1][0] == '/')
		ft_cd_absolute(data, cmd, pwd);
	else
		ft_cd_relative(data, cmd, pwd);
}

/*
**	check arg after cd ( - ; ~ ; path)
*/
static int	ft_check_dir(t_data *data, t_cmd *cmd)
{
	int		rv;

	rv = 0;
	if (cmd->args[1])
	{
		if (!ft_strncmp(cmd->args[1], "-", 1))
			return (rv = ft_check_minus(data));
		if (!ft_strncmp(cmd->args[1], "~", 1))
			rv = ft_check_tilde(data);
		else if (chdir(cmd->args[1]) == 0)
			rv = 1;
		else
			ft_errno(cmd->args[1], 1, data, false);
	}
	if (!cmd->args[1])
		rv = ft_check_home(data);
	return (rv);
}

/*
**	if the direction works -> we change pwd + oldpwd
*/
void	ft_cd(t_data *data, t_cmd *cmd)
{
	if (ft_check_dir(data, cmd))
		ft_change_pwd(data, cmd);
}
