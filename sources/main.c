/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/12 15:46:18 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**my_env;
	char	**my_prompt;
	// char	**path;

	(void)argc;
	(void)argv;
	my_env = env;
	// path = ft_split(getenv("PATH"), ':');
	// execve(*path, &argv[2], env);
	
	av_init_signal();
	while (19)
	{
		prompt = readline("SHELLMINI$>");
		if (prompt)
		{
			my_prompt = ft_split(prompt, ' ');
			add_history(prompt);
			free(prompt);
			if (!my_prompt || !*my_prompt)
				continue ;
			if (ft_is_builtin(my_prompt) == false)
				cmd_exec(my_prompt, my_env);
			else
				ft_builtin(my_prompt, my_env);
		}
		av_signal();
	}
		// free le **my_prompt
	system("leaks minishell");
	return (0);
}

/* pourquoi apres un exec, on sort du programme */

/*
**	Affichage env OK + copie de l'env
**	besoin de re-avoir le prompt après l'execution d'une commande
**	pour avoir le PATH :
**	path = getenv("PATH");
**	printf("PATH == %s\n", path);
**	https://dev.to/harshbanthiya/writing-my-own-minimal-shell-in-c-part-2-the-builtin-functions-and-general-interpretation-4lnb
**	segfault quand ctrl + d origine ?
**	gerer les maj/minuscule des commandes -> mettre tout en minuscule pour le char *cmd
**	probleme signaux affichage ^C quand input vide
**	apres l'arret d'un process ctrl+c 
**	check ft_list_sort + ft_sorted_list_insert pour export
**	a voir si je peux prendre que certains var de l'env ou je dois tout prendre
**	BUG AVEC CAT -> NE LIT PAS MAIS ACTIVE LE STDIN
*/
