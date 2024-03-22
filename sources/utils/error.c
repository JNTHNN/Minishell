/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:26:11 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/22 13:51:08 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error(int err_code)
{
	if (err_code == E_QUOTES)
		ft_putstr_fd(ERR_QUOTES, STDERR_FILENO);
	else if (err_code == E_PIPE)
		ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
	else if (err_code == E_MEM)
		ft_putstr_fd(ERR_MEM, STDERR_FILENO);
}

void	ft_throw_error(t_data *data, int err_code)
{
	ft_print_error(err_code);
	// free all stuff (data...) before relaunch the program
	(void)data;
}
