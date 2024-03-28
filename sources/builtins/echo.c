/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:13:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/28 18:25:47 by jgasparo         ###   ########.fr       */
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

// static void	return_value(void)
// {
// 	printf("15");
// }

void	ft_echo(char **str)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (str && str[i] != NULL && ft_check_option(str[i]) == 1)
	{
		option = 1;
		i++;
	}
	if (str[1] && !ft_strncmp(str[1], "$?", 2))
	{
		ft_putstr_fd("C'est good le $?", 1);
		if (option == 0)
			ft_putstr_fd("\n", 1);
		return ;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
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
