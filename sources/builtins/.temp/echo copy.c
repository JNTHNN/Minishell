/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:13:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/30 12:36:53 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Ecrit l'argument dans le terminal, si flag -n (voir si besoin checker ici)
**	ou sera fait en amont
**	remplacer *str par *arg et int flg par char *flag
**	echo ~ = print le HOME
**	echo ~+ = print le PWD
**	echo ~+text = PWD + texte.
*/

static int	ft_check_option(char *option)
{
	int	i;

	i = 0;
	if (option[0] != '-')
		return (0);
	i++;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
/*	VA PRINT LA VALEUR RETOUR DE PROCESS (EXIT)	*/

// static int	dollar_mark(t_data *data)
// {
// 	if (data->cmd->args[1] || data->cmd->args[2])
// 	{
// 		if ((!ft_strncmp(data->cmd->args[1], "$?", 2)
// 			|| !ft_strncmp(data->cmd->args[2], "$?", 2)))
// 		{
// 			ft_putstr_fd("C'est good le $?", 1);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

void	ft_echo(t_data *data)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (data->cmd->args && data->cmd->args[i] != NULL
		&& ft_check_option(data->cmd->args[i]) == 1)
	{
		option = 1;
		i++;
	}
	// dollar_mark(data, option);
	// if (dollar_mark(data))
	// {
		while (data->cmd->args[i])
		{
			ft_putstr_fd(data->cmd->args[i], 1);
			if (data->cmd->args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		// }
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}

/* EXTRA A IMPLEMENTER  = ECHO ~ et ECHO ~+ */

		// if (!ft_strncmp(&str[1][0], "~", 1))
		// {
		// 	if (!ft_strncmp(&str[1][1], "+", 1))
		// 	{
		// 		printf("%s", getenv("PWD"));
		// 	}
		// 	printf("%s", getenv("HOME"));
		// 	if (option == 0)
		// 		ft_putstr_fd("\n", 1);
		// 	break ;
		// }
