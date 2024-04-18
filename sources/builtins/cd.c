/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/10 19:17:51 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GERER TOUT LES RACCOURCIS
// CD SANS ARGS -> $HOME √
// CD - -> OLD_PWD + PRINT 
// CD ~ -> $HOME √
// CD .. -> REPERTOIRE PARENT √
// CD / -> RACINE SYSTEME √
// CD . -> RIEN REPERTOIRE ACTUEL √
// CD ~user -> REPERTOIRE PERSO DE L'USER SPECIFIE
// UNSET PWD NE FAIT RIEN MAIS EN CREE UN APRES L'ACTION DE CD

static void	ft_change_pwd(t_data *data, t_cmd *cmd)
{
	char	*pwd;

	pwd = ft_getenv(data, "PWD");
	if (!pwd)
		ft_putstr_fd("No PWD, No party\n", STDERR_FILENO);
	if (!cmd->args[1])
		ft_cd_home(data, pwd);
	else if (cmd->args[1][0] == '/')
		ft_cd_absolute(data, cmd, pwd);
	else
		ft_cd_relative(data, cmd, pwd);
}

static int	ft_check_dir(t_data *data, t_cmd *cmd)
{
	int		rv;

	rv = 0;
	if (cmd->args[1])
	{
		if (!ft_strncmp(cmd->args[1], "-", 1))
			rv = ft_check_minus(data);
		if (!ft_strncmp(cmd->args[1], "~", 1))
			rv = ft_check_tilde(data);
		else if (chdir(cmd->args[1]) == 0)
			rv = 1;
		else 
			perror("cd direction");
	}
	if (!cmd->args[1])
		rv = ft_check_home(data);
	return (rv);
}

void	ft_cd(t_data *data, t_cmd *cmd)
{
	if (ft_check_dir(data, cmd))
		ft_change_pwd(data, cmd);
}
