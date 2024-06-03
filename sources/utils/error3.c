/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:02:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/03 15:08:11 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_exec_error_dir(t_data *data, int err_code)
{
	errno = 0;
	ft_putstr_fd(START_ERR, STDERR_FILENO);
	ft_putstr_fd(data->err_info, STDERR_FILENO);
	if (err_code == E_DIR)
	{
		ft_putstr_fd(ERR_DIR, STDERR_FILENO);
		ft_errno(NULL, EX_NOEXEC, data);
	}
}
