/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JG_exit_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:36:19 by jgasparo          #+#    #+#             */
/*   Updated: 2023/11/27 10:06:32 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	exit sans rien va quitter le processus en cours donc le minishell
**	veuillez a bien free tout ce qui a pu etre allouer
**
*/

#include "../../includes/minishell.h"

void	exit_builtins(void)
{
	ft_putendl_fd("exit", 1);
	system("leaks minishell");
	exit(EXIT_SUCCESS);
}