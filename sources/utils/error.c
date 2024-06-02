/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:26:11 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/02 20:47:25 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints an error message for redirection errors 
** based on the error code.
*/
static void	ft_print_redir_error(int err_code)
{
	g_exit_code = EX_USAGE;
	ft_putstr_fd(ERR_REDIR, STDERR_FILENO);
	if (err_code == E_REDIR_OUT)
		ft_putstr_fd("`>'\n\033[0m", STDERR_FILENO);
	else if (err_code == E_REDIR_OUT_T)
		ft_putstr_fd("`>>'\n\033[0m", STDERR_FILENO);
	else if (err_code == E_REDIR_IN)
		ft_putstr_fd("`<'\n\033[0m", STDERR_FILENO);
	else if (err_code == E_REDIR_HD)
		ft_putstr_fd("`<<'\n\033[0m", STDERR_FILENO);
	else if (err_code == E_PIPE)
		ft_putstr_fd("`|'\n\033[0m", STDERR_FILENO);
	else
		ft_putstr_fd("`newline'\n\033[0m", STDERR_FILENO);
}

/*
** Prints an error message for execution errors 
** based on the error code.
*/
static void	ft_print_exec_error(int err_code, t_data *data)
{
	if (err_code == E_EXECVE)
		ft_errno(data->err_info, EX_NOEXEC, data);
	else
	{
		errno = 0;
		ft_putstr_fd(START_ERR, STDERR_FILENO);
		ft_putstr_fd(data->err_info, STDERR_FILENO);
		if (err_code == E_DIR)
		{
			ft_putstr_fd(ERR_DIR, STDERR_FILENO);
			ft_errno(NULL, EX_NOEXEC, data);
		}
		else if (err_code == E_NOTF)
			ft_putstr_fd(ERR_CMD, STDERR_FILENO);
		else if (err_code == E_PATH)
			ft_putstr_fd(ERR_ENV_OPEN, STDERR_FILENO);
		else if (err_code == E_EXECVE_2)
			ft_putstr_fd(ERR_ENV_OPEN, STDERR_FILENO);
		else
			ft_errno(data->err_info, EX_NOTFOUND, data);
		ft_errno(NULL, EX_NOTFOUND, data);
	}
}

/*
** Prints a general error message based on the error code.
*/
static void	ft_print_error(int err_code, t_data *data)
{
	g_exit_code = EX_MISCERROR;
	if (err_code == E_QUOTES)
		ft_putstr_fd(ERR_QUOTES, STDERR_FILENO);
	else if (err_code == E_MEM)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	else if (err_code <= E_REDIR && err_code >= E_REDIR_OUT_T)
		ft_print_redir_error(err_code);
	else if (err_code == E_OPEN)
		ft_errno(data->err_info, EXEC_FAIL, data);
	else if (err_code == E_DUP)
		ft_errno(NULL, EX_MISCERROR, data);
	else if ((err_code <= E_EXECVE && err_code >= E_EXECVE_2)
		|| err_code == E_PATH)
		ft_print_exec_error(err_code, data);
	else if (err_code == E_CLOSE)
		ft_errno(NULL, EX_MISCERROR, data);
	else if (err_code == E_ENV)
		ft_print_env_error(data);
	else if (err_code == E_CWD)
		ft_putstr_fd(ERR_CWD, STDERR_FILENO);
	else if (err_code == E_VAR_ID)
		ft_print_unset_error(ERR_VAR_ID, data);
	else
		ft_putstr_fd(ERR_UNDEF, STDERR_FILENO);
}

/*
** Prints and handles an error based on the error code,
** then frees resources.
*/
static void	ft_throw_error(t_data *data, int err_code)
{
	ft_print_error(err_code, data);
	ft_free_if_error(data);
}

/*
** Handles errors by printing and managing resources,
** returning status.
*/
int	ft_handle_error(t_data *data, int ret)
{
	if (ret)
	{
		ft_throw_error(data, ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
