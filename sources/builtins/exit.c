/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:36:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/23 13:13:06 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	exit sans rien va quitter le processus en cours donc le minishell
**	veuillez a bien free tout ce qui a pu etre allouer
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
		exit_status = EXIT_FAILURE;
		return (exit_status);
	}
	if (cmd->args[1] && !ft_atoi(cmd->args[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
		exit_status = EXIT_FAILURE;
	}
	if (cmd->args[1] && ft_atoi(cmd->args[1]))
		exit_status = ft_atoi(cmd->args[1]);
	ft_free_data(data);
	exit(exit_status);
	return (exit_status);
}
