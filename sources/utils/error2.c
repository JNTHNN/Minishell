/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:28 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/15 15:40:40 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_errno(char *s, int code, t_data *data)
{
	if (errno != 0)
	{
		ft_putstr_fd(START_ERR, STDERR_FILENO);
		perror(s);
		ft_putstr_fd(END_RST, STDERR_FILENO);
	}
	else
		ft_putstr_fd(s, STDERR_FILENO);
	if (code)
		g_exit_code = code;
	if (code == E_MEM)
		ft_free_data(data);
	if (data->nb_of_cmds != 1 || (!data->cmd->is_builtin && code != EXEC_FAIL))
	{
		ft_free_if_error(data);
		exit(g_exit_code);
	}
}

void	ft_handle_arg_error(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
