/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/08 14:48:22 by jgasparo         ###   ########.fr       */
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

static void	ft_change_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_getenv(data, "PWD");
	printf("OU JE VAIS ?\n");
	if (!pwd)
		ft_putstr_fd("No PWD, No party\n", STDERR_FILENO);
	if (!data->cmd->args[1])
{		printf("JE VAIS DANS LA 1ERE\n");
		ft_cd_home(data, pwd);}
	else if (data->cmd->args[1][0] == '/')
{		printf("JE VAIS DANS LA 2EME\n");
		ft_cd_absolute(data, pwd);}
	else
{		printf("JE VAIS DANS LA 3EME\n");
		ft_cd_relative(data, pwd);}
}

static int	ft_check_dir(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME=");
	printf("HOME [%s]\n", home);
	if (!home)
	{
		perror("No HOME, No party");
		return (0);
	}
	if (!data->cmd->args[1] || !ft_strncmp(data->cmd->args[1], "~", 1))
	{
		if (chdir(home + 5) == -1)
		{
			perror("cd home");
			return (0);
		}
	}
	else if (chdir(data->cmd->args[1]) == -1)
	{
		perror("cd direction");
		return (0);
	}
	return (1);
}

void	ft_cd(t_data *data)
{
	if (ft_check_dir(data))
		ft_change_pwd(data);
}
