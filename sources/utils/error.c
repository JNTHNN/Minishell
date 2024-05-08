/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:26:11 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/08 18:17:15 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print_redir_error(int err_code)
{
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
	g_exit_code = 2;
}

static void	ft_print_error(int err_code, t_data *data)
{
	if (err_code == E_QUOTES)
		ft_putstr_fd(ERR_QUOTES, STDERR_FILENO);
	else if (err_code == E_MEM)
		ft_putstr_fd(ERR_MEM, STDERR_FILENO);
	else if (err_code <= E_REDIR && err_code >= E_REDIR_OUT_T)
		ft_print_redir_error(err_code);
	else if (err_code == E_OPEN)
	{
		g_exit_code = EXIT_FAILURE;
		ft_printf("❌\033[0;31m %s:", data->err_info);
		ft_putstr_fd(ERR_OPEN, STDERR_FILENO);
	}
	else if (err_code == E_DUP)
		ft_putstr_fd(ERR_DUP, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_UNDEF, STDERR_FILENO);
}

static void	ft_throw_error(t_data *data, int err_code)
{
	ft_print_error(err_code, data);
	// g_exit_code = err_code;
	ft_free_if_error(data);
}

int	ft_handle_error(t_data *data, int ret)
{
	(void)data;
	if (ret)
	{
		ft_throw_error(data, ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_handle_arg_error(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(1);
	}
}

void	ft_errno(char *s, int code, t_data *data, int flag)
{
	if (s)
	{
		if (errno != 0)
		{
			ft_putstr_fd("❌\033[0;31m minibash: ", 2);
			perror(s);
			ft_putstr_fd("\033[0m", 2);
		}
		else
			ft_putstr_fd(s, 2);
	}
	if (code)
	{
		g_exit_code = code;
		printf("EXITCODE APRES = %d\n", g_exit_code);
	}
	if (flag)
	{
		ft_free_if_error(data);
		exit(g_exit_code);
	}
}
