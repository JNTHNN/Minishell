/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:32:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/02 18:34:22 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Prints the error string with the arg in question
*/
void	ft_print_err_exit(char *arg)
{
	ft_putstr_fd(START_EXIT, STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(ERR_NUM_ARG, STDERR_FILENO);
	}
	else
		ft_putstr_fd(ERR_TOO_ARG, STDERR_FILENO);
}
