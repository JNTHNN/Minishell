/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:36:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/02 17:13:40 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data, t_cmd *cmd)
{
	u_int64_t	exit_status;
	int			flag;

	exit_status = (u_int8_t)g_exit_code;
	flag = 0;
	if (data->nb_of_cmds == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->args[1])
	{
		exit_status = ft_atol(cmd->args[1], &flag);
		if (flag || !cmd->args[1][0] || (flag && ft_tablen(cmd->args) > 2))
		{
			ft_print_err_exit(cmd->args[1]);
			exit_status = 255;
		}
	}
	if (!flag && ft_arrlen(cmd->args) > 2)
	{
		ft_print_err_exit(NULL);
		g_exit_code = EXIT_FAILURE;
		return (g_exit_code);
	}
	ft_free_data(data);
	return (exit(exit_status), EXIT_SUCCESS);
}
