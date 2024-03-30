/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:19:45 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/30 19:36:28 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	La fonction getcwd() copie le chemin d'accès absolu du répertoire de 
**	travail courant dans la chaîne pointée par buf, qui est de longueur size.
*/

/*	(void)data for the moment	*/

void	ft_pwd(t_data *data)
{
	static char	cwd[PATH_MAX];

	(void)data;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd()");
}
