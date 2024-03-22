/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:36:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/22 14:05:35 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	exit sans rien va quitter le processus en cours donc le minishell
**	veuillez a bien free tout ce qui a pu etre allouer
**
*/

#include "../../includes/minishell.h"

void	ft_exit_builtins(void)
{
	ft_putendl_fd("exit", 1);
	//system("leaks minishell");
	exit(EXIT_SUCCESS);
}
