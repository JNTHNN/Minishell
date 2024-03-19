/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/18 12:10:36 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**my_prompt;

	if (argc != 1 || argv[1])
		ft_throw_error(0, ERR_ARG);
	data.env = envp;
	data.env_cpy = ft_arrcpy(envp);
	ft_init_signal();
	while (true)
	{
		data.input = readline(PROMPT);
		if (data.input)
		{
			ft_tokenize(&data);
			my_prompt = ft_split(data.input, ' ');
			add_history(data.input);
			free(data.input);
			if (!my_prompt || !*my_prompt)
				continue ;
			if (ft_is_builtin(my_prompt) == false)
				cmd_exec(my_prompt, data.env);
			else
				ft_builtin(my_prompt, data.env);
		}
		ft_signal();
	}
		// free le **my_prompt
	system("leaks minishell");
	return (EXIT_SUCCESS);
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
