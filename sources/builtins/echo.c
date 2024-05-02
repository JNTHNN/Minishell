/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:13:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/02 19:48:40 by jgasparo         ###   ########.fr       */
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
**	echo ~- = print le OLD_PWD
*/

/*
**	checker for -n | return 0 if not
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


// static int	ft_check_tilde(char *option)
// {
// 	int	i;

// 	i = 0;
// 	if (option[0] != '~')
// 		return (0);
// 	if (option[0] == '~' && !option[1])
// 		return (1);
// 	return (0);
// }

void	ft_echo(t_data *data, t_cmd *cmd)
{
	int	i;
	int	option;

	(void)data;
	i = 1;
	option = 0;
	while (cmd->args && cmd->args[i] != NULL
		&& ft_check_option(cmd->args[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}

/* EXTRA A IMPLEMENTER  = ECHO ~ et ECHO ~+ */
