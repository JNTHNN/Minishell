/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/06 21:13:55 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GERER TOUT LES RACCOURCIS
// CD SANS ARGS -> $HOME √
// CD - -> OLD_PWD
// CD ~ -> $HOME √
// CD .. -> REPERTOIRE PARENT √
// CD / -> RACINE SYSTEME √
// CD . -> RIEN REPERTOIRE ACTUEL √
// CD ~user -> REPERTOIRE PERSO DE L'USER SPECIFIE
// UNSET PWD NE FAIT RIEN MAIS EN CREE UN APRES L'ACTION DE CD

static void	ft_change_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_getenv(data, "PWD");
	if (!pwd)
		ft_putstr_fd("No PWD, No party\n", STDERR_FILENO);
	if (!data->cmd->args[1])
		ft_cd_home(data, pwd);
	else if (data->cmd->args[1][0] == '/')
		ft_cd_absolute(data, pwd);
	else
		ft_cd_relative(data, pwd);
}

static int	ft_check_dir(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME=");
	if (!home)
	{
		perror("No HOME, No party");
		return (0);
	}
	if (data->cmd->args[1])
	{
		if (!data->cmd->args[1] && chdir(home) == -1)
		{
			perror("cd home");
			return (0);
		}
		else if (chdir(data->cmd->args[1]) == -1)
		{
			perror("cd direction");
			return (0);
		}
	}
	return (1);
}

void	ft_cd(t_data *data)
{
	if (ft_check_dir(data))
		ft_change_pwd(data);
}
