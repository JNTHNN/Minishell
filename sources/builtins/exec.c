/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/19 15:52:41 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// doit faire en sorte que je checke tout les possibilités des chemin
// du path 

#include "../../includes/minishell.h"
#include <string.h>

// ameliorer strcat pour faire l'action en une seule fonction
// comme ca je lstiter avec, dans un lstmap


static char **ft_pathiter(char **path, char *cmd)
{
	// but : ajouter au path "/" + cmd et retourner le tableau
	
	char *new_cmd;
	char *temp;
	
	new_cmd = ft_strjoin("/", cmd);
	while (*path)
	{
		temp = ft_strjoin(*path, new_cmd);
		*path = temp;
		path++;
	}
	return(path);
}

static char **ft_path_abs(char **env, char *cmd)
{
	char *path;
	char **my_path;
    (void)env;
	path = getenv("PATH");
	my_path = ft_split(path, ':');
	ft_pathiter(my_path, cmd);
	return(my_path);
}
 
int ft_create_exec(char **argv, char **env)
{
    char	**progpath;
    char	*test[]={"ls", (char*)0};
	// le test doit contenir les flags/options si il y'en a
	// ici ca prend en compte le [1]

    progpath = ft_path_abs(env, argv[0]);
    if (!progpath)
    {
        perror("path");
        exit(EXIT_FAILURE);
    }
    while (*progpath)
    {
        if (access(*progpath, F_OK) == 0)
        {
            if (execve(*progpath, test, env) == -1)
            {
                perror("command");
                exit(EXIT_FAILURE);
            }
        }
        progpath++;
    }
    return (EXIT_FAILURE);
}
	// progpath = path_abs(env, argv[0]);
	// while (*progpath)
	// {
	// 	if (execve(*progpath, test, env) == -1)
	// 		progpath++;
	// 	else
	// 	{
	// 		perror("command");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }



/*	On fork	
**	PID == -1 : ERROR
**	SI LE FORK REUSSIT, LE PROCESSUS PERE ATTEND LE PROCESSUS FILS
**	PID > 0 :  ON BLOCK LE PROCESSUS PERE JUSQU'A QUE L'ENFANT TERMINE (WAITPID)
**	PUIS ON KILL LE PROCESSUS ENFANT
**	ELSE (PID == 0) : LE PROCESSUS ENFANT EXECUTE LA COMMANDE*/

void	ft_cmd_exec(char **cmd, char **my_env)
{
	pid_t	pid;
	int		status;
	char	*test[]={"ls", (char*)0};

	pid = fork();
	status = 0;
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		if (!ft_strncmp(*cmd, "/", 1))
        {
            if (execve(cmd[0], test, my_env) == -1)
                exit(EXIT_FAILURE);
            else
                exit(EXIT_SUCCESS);
        }
        else
        {
            if (ft_create_exec(cmd, my_env) == EXIT_FAILURE)
            {
                perror("command not found");
                exit(EXIT_FAILURE);
            }
            else
                exit(EXIT_SUCCESS);
        }
	}
}


/*	CREER UN FLAG POUR CREAT_EXEC SI -1 DNC PAS DE COMMANDE -> EXIT POUR KILL LE PROCESSUS*/