/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/26 22:40:46 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		ret;
	char	**my_prompt;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(0);
	}
	data.env = envp;
	data.env_cpy = ft_arrcpy(envp);
	ft_init_signal();
	while (true)
	{
		data.input = readline(PROMPT);
		if (ft_trim_input(&data.input))
			return (E_MEM);
		if (data.input && data.input[0])
		{
			add_history(data.input);
			ret = ft_tokenize(&data);
			if (ret)
			{
				ft_throw_error(&data, ret);
				continue ;
			}
			my_prompt = ft_split(data.input, ' ');
			free(data.input);
			ret = ft_parse(&data);
			if (ret)
			{
				ft_throw_error(&data, ret);
				continue ;
			}
			if (!my_prompt || !*my_prompt)
				continue ;
			if (ft_is_builtin(my_prompt) == false)
				ft_cmd_exec(my_prompt, data.env);
			else
				ft_builtin(my_prompt, data.env);
		// free le **my_prompt
			free_arr(my_prompt);
		}
		ft_signal();
	}
	// free le **my_prompt
	free_arr(my_prompt);
	//system("leaks minishell");
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
