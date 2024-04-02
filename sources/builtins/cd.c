/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/02 15:46:30 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

/*
**	devoir changer la var PWD avec la nouvelle dest
*/

// void	cd_builtins(char *str, char **env)
// {
// 	char	*pos;
// 	char	*here = NULL;
// 	char	*final = NULL;
// 	(void)env;
// 	pos = getenv("PWD");
// 	if (!chdir(str))
// 	{
// 		opendir(str);
// 	}
// 	printf("on est ici -> %s\n", getcwd(here, 0));
// 	final = ft_strjoin(pos, str);
// 	printf("final pos -> %s\n", final);
// }

/* besoin de */
void	ft_cd(t_data *data)
{
	char *pos;
	char *old_pos;

	pos = getenv("PWD");
	old_pos = getenv("OLD_PWD");
	printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
	if (chdir(data->cmd->args[1]) == -1)
		perror("chdir()");
	printf("CD EXECUTE WITH DIRECTORY [%s] ---\n", data->cmd->args[1]);
	pos = getenv("PWD");
	old_pos = getenv("OLD_PWD");
	printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
}

// Lorsque vous exécutez un programme, celui-ci est lancé dans un nouveau processus.
// Ce nouveau processus a son propre environnement, qui est une copie de l'environnement
// du processus parent (dans ce cas, votre shell).
// Lorsque vous changez de répertoire à l'intérieur de ce nouveau processus
// (par exemple, en utilisant la fonction chdir() dans votre programme), 
// cela n'affecte pas le répertoire de travail du processus parent. 
// C'est pourquoi, après l'exécution de votre programme, vous vous retrouvez toujours dans le même répertoire dans votre shell.
//
// Si vous voulez changer le répertoire de travail de votre shell, vous devez utiliser la commande cd directement dans le shell,
// et non dans un programme exécuté à partir du shell. Dans le contexte de votre shell personnalisé,
// vous devrez implémenter la commande cd comme une fonction intégrée (ou "builtin") de votre shell, 
// plutôt que comme une commande externe.
