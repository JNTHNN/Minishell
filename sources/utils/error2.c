/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:28 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/05 10:44:37 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles errors by printing messages and exiting if necessary.
*/
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
	if (code == E_OPEN)
	{
		close(STDOUT_FILENO);
		g_exit_code = EXEC_FAIL;
	}
	if (data->nb_of_cmds != 1
		|| (!data->cmd->is_builtin && code != EXEC_FAIL))
	{
		ft_free_data(data);
		exit(g_exit_code);
	}
}

/*
** Prints environment-related error messages.
*/
void	ft_print_env_error(t_data *data)
{
	ft_putstr_fd(START_ERR, STDERR_FILENO);
	ft_putstr_fd(data->err_info, STDERR_FILENO);
	ft_putstr_fd(ERR_ENV_ARG, STDERR_FILENO);
	errno = 0;
	ft_errno(NULL, EX_NOTFOUND, data);
}

/*
** Handles argument errors and exits if incorrect arguments are provided.
*/
void	ft_handle_arg_error(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

/*
** Prints unset command-related error messages.
*/
void	ft_print_unset_error(char *err, t_data *data)
{
	g_exit_code = EXEC_FAIL;
	ft_putstr_fd(START_UNSET, STDERR_FILENO);
	ft_putstr_fd(data->err_info, STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
}

void	ft_print_export_error(char *err, t_data *data)
{
	ft_putstr_fd(START_EXPORT, STDERR_FILENO);
	ft_putstr_fd(data->err_info, STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_errno(NULL, EXEC_FAIL, data);
}
