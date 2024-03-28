/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:12:21 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/28 15:47:11 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

/*
**	Envoyez l'option pour echo;
**	Envoyez le chemin relatif ou absolu pour cd
**	si env est suivi arg ou autre -> retourner message erreur
**	REMOVE SYSTEM
**	./minishell = creation d'un processus enfant SHLVL + 1
*/


// doit faire en sorte que je checke tout les possibilités des chemin
// du path 

// static char *path_cmd(char *cmd)
// {
// 	char *path = getenv("PATH");
// 	char **path_split;

// 	// printf("%s", path);
// 	path_split = ft_split(path, ':');
// 	char *dest = malloc(sizeof(char) + ft_strlen(cmd) + 1);
// 	strcat(dest, path_split[3]);
// 	strcat(dest, "/");
// 	strcat(dest, cmd);
// 	printf(" result : %s\n", dest);
	
// 	return (dest);

// }

// static void create_exec(char **argv, char **env)
// {
// 	char	*progpath;
// 	char	*test[]={"Test", "test_execve.c",(char*)0};
// 	// le test doit contenir les flags/options si il y'en a
// 	// ici ca prend en compte le [1]

// 	progpath = path_cmd(argv[0]);
// 	if (execve(progpath, test, env) == -1)
// 		perror("shell");
// 	exit(EXIT_FAILURE);
// }

// bool	ft_is_builtin(char *name)
// {
// 	int			i;
// 	static char	*builtin_tab[8] = {"echo", "cd", "pwd", "export", "unset", \
// 	"env", "exit", NULL};

// 	i = 0;
// 	while (builtin_tab[i])
// 	{
// 		if (!ft_strncmp(name, builtin_tab[i], ft_strlen(name)))
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

bool    ft_is_builtin(char *name)
{
    int         i;
    static char *builtin_tab[8] = {"echo", "cd", "pwd", "export", "unset", \
    "env", "exit", NULL};

    i = 0;
    if (name)
    {
        while (builtin_tab[i])
        {
            if (!ft_strncmp(name, builtin_tab[i], ft_strlen(name)))
                return (true);
            i++;
        }
    }
    return (false);
}

void	ft_builtin(char **arg, char **my_env)
{
	if (!ft_strncmp(arg[0], "echo", 4))
		ft_echo(arg);
	if (!ft_strncmp(arg[0], "cd", 2))
		// cd_builtins(prompt + 3, my_env);
		ft_cd(arg);
	if (!ft_strncmp(arg[0], "pwd", 3))
		ft_pwd();
	if (!ft_strncmp(arg[0], "export", 6))
		ft_export(arg, my_env);
	if (!ft_strncmp(arg[0], "unset", 5))
		return ;
	if (!ft_strncmp(arg[0], "env", 3))
		ft_env(my_env);
	if (!ft_strncmp(arg[0], "exit", 4))
		ft_exit();
	if (!ft_strncmp(arg[0], "system", 6))
		system("leaks minishell");
	if (!ft_strncmp(arg[0], "xxx", 3))
	{
		while (*arg)
			printf("%s\n", *arg++);
	}
	// else
	// 	create_exec(arg, my_env);

	// create_exec(&prompt, my_env);
		// test_exec(prompt, my_env);
	// if (!ft_strncmp(prompt, "history", 7))
	// 	builtin_hist(history_list);
}
