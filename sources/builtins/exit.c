/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:36:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/25 09:59:10 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	exit sans rien va quitter le processus en cours donc le minishell
**	veuillez a bien free tout ce qui a pu etre allouer
**
*/

#include "../../includes/minishell.h"

int	ft_exit(t_data *data, t_cmd *cmd)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_free_data(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
