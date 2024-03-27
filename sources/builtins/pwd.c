/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:19:45 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/27 12:51:44 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	La fonction getcwd() copie le chemin d'accès absolu du répertoire de 
**	travail courant dans la chaîne pointée par buf, qui est de longueur size.
*/

// void	builtin_pwd(void)
// {
// 	// printf("%s\n", getenv("PWD"));
// 	/* voir si cwd n'est pas mieux */
// 	char	*where;
	
// 	where = NULL;
// 	printf("%s\n", getcwd(where, 0));
// }

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd()");
}