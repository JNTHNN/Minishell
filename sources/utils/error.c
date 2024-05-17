/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:26:11 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/17 13:45:55 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_print_exec_error(int err_code, t_data *data)
{
	if (err_code == E_EXECVE)
		ft_errno(data->err_info, EX_NOEXEC, data);
	else if (err_code == E_DIR)
	{
		errno = EISDIR;
		ft_errno(data->err_info, EX_NOEXEC, data);
	}
	else if (err_code == E_NOTF)
	{
		ft_putstr_fd(START_ERR, STDERR_FILENO);
		ft_putstr_fd(data->err_info, STDERR_FILENO);
		ft_putstr_fd(ERR_CMD, STDERR_FILENO);
		errno = 0;
		ft_errno(NULL, EX_NOTFOUND, data);
	}
	else
		ft_errno(data->err_info, EX_NOTFOUND, data);
}

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
	else if (err_code <= E_EXECVE && err_code >= E_EXECVE_2)
		ft_print_exec_error(err_code, data);
	else if (err_code == E_CLOSE)
		ft_errno(NULL, EX_MISCERROR, data);
	else if (err_code == E_ENV)
		ft_print_env_error(data);
	else if (err_code == E_CWD)
		ft_putstr_fd(ERR_CWD, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_UNDEF, STDERR_FILENO);
}

static void	ft_throw_error(t_data *data, int err_code)
{
	ft_print_error(err_code, data);
	ft_free_if_error(data);
}

int	ft_handle_error(t_data *data, int ret)
{
	if (ret)
	{
		ft_throw_error(data, ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
