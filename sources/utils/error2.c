/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:28 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/13 22:33:39 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_errno(char *s, int code, t_data *data)
{
	if (errno != 0)
	{
		ft_putstr_fd("❌\033[0;31m minibash: ", STDERR_FILENO);
		perror(s);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
	}
	else
		ft_putstr_fd(s, STDERR_FILENO);
	if (code)
		g_exit_code = code;
	if (code == E_MEM)
		ft_free_data(data);
	if (data->nb_of_cmds != 1)
	{
		ft_free_if_error(data);
		exit(g_exit_code);
	}
}

void    ft_errno_exec(t_data *data, char *arg)
{
    ft_putstr_fd("❌\033[0;31m minibash: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    ft_putstr_fd("\033[0m", STDERR_FILENO);
    ft_errno(NULL, 127, data);
}