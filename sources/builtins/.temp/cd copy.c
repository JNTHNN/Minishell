/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/03 16:57:30 by jgasparo         ###   ########.fr       */
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

// GERER TOUT LES RACCOURCIS
// CD SANS ARGS -> $HOME
// CD - -> OLD_PWD
// CD ~ -> $HOME
// CD .. -> REPERTOIRE PARENT
// CD / -> RACINE SYSTEME
// CD . -> RIEN REPERTOIRE ACTUEL
// CD ~user -> REPERTOIRE PERSO DE L'USER SPECIFIE
// UNSET PWD NE FAIT RIEN MAIS EN CREE UN APRES L'ACTION DE CD

// doit faire l'expand de ..

// tab de tab + recursive strrchr + memset

char	*ft_set_pwd(t_data *data, char *pwd)
{
	(void)pwd;
	// int	i;
	char *pos;

	// i = 0;
	pos = getenv("PWD");
	if (data->cmd->args[1])
	{
		if (data->cmd->args[1])
		pos = ft_strjoin(pos, "/");
		pos = ft_strjoin(pos, data->cmd->args[1]);
		return (pos);
	}
	return (pos);
}

char	*ft_set_oldpwd(t_data *data, char *old_pwd)
{
	(void)old_pwd;

	char	*pos;
	int		start;
	int		i;

	i = 0;
	pos = NULL;
	start = ft_strlen(data->cmd->args[1]) + 1;
	// remove = ft_strrchr(getenv("PWD"), '/');
	while(data->env[i])
	{
		if (!getenv("OLD_PWD"))
			data->env[i] = ft_strdup(getenv("PWD"));
		if (!ft_strncmp(data->env[i], "OLD_PWD=", 7))
			ft_memset(ft_strrchr(data->env[i], '/'), 0, start);
		i++;
	}
	return (pos);
}

void	ft_cd(t_data *data)
{
	// j'ai besoin de PWD / OLD_PWD / HOME
	if 
}

// void	ft_cd(t_data *data)
// {
// 	char *pos;
// 	char *old_pos;

// 	pos = getenv("PWD");
// 	old_pos = getenv("OLD_PWD");
// 	printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
// 	printf("--- CD EXECUTE WITH DIRECTORY [%s] ---\n", data->cmd->args[1]);
// 	if (chdir(data->cmd->args[1]) == -1)
// 		perror("chdir()");
// 	else
// 		pos = ft_set_pwd(data, NULL);
// 	// pos = getenv("PWD");
// 	// old_pos = getenv("OLD_PWD");
// 	old_pos = ft_set_oldpwd(data, NULL);
// 	printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
// 	// pos = ft_strchr(pos, '/');
// 	// old_pos = ft_strrchr(pos, '/');
// 	// printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
// }

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
