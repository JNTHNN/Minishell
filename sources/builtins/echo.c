/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:13:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/16 11:35:09 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
**	shortcuts for ~ -> $HOME | ~+ -> $PWD | ~- -> $OLDPWD
*/
static char	*ft_extra(t_data *data, char *s)
{
	if (!ft_strncmp(s, TILDE, 2) && ft_getenv(data, HOME))
		s = ft_getenv(data, HOME) + 5;
	else if (!ft_strncmp(s, TPLUS, 3) && ft_getenv(data, PWD))
		s = ft_getenv(data, PWD) + 4;
	else if (!ft_strncmp(s, TMINUS, 3) && ft_getenv(data, OLDPWD))
		s = ft_getenv(data, OLDPWD) + 7;
	return (s);
}

void	ft_echo(t_data *data, t_cmd *cmd)
{
	int	i;
	int	option;

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
		cmd->args[i] = ft_extra(data, cmd->args[i]);
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}
