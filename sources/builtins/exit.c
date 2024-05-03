/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:36:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 20:51:45 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	exit sans rien va quitter le processus en cours donc le minishell
**	veillez a bien free tout ce qui a pu etre allouer
**
*/

#include "../../includes/minishell.h"

int	ft_exit(t_data *data, t_cmd *cmd)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->args[1] && ft_atoi(cmd->args[1]) && cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_exit_code = EXIT_FAILURE;
		return (g_exit_code);
	}
	if (cmd->args[1] && !ft_atoi(cmd->args[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required",
			STDERR_FILENO);
		exit_status = 255;
	}
	if (cmd->args[1] && ft_atoi(cmd->args[1]))
		exit_status = ft_atoi(cmd->args[1]);
	ft_free_data(data);
	return (exit(exit_status), EXIT_SUCCESS);
}
