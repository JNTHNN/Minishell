/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/27 11:12:32 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "❌\033[0;31m  Minishell doesn't accept arguments \033[0m\n"
# define ERR_QUOTES "❌\033[0;31m Unexpected token : unclosed quote \033[0m\n"
# define ERR_REDIR "❌\033[0;31m Syntax error near unexpected token "
# define ERR_MEM "❌\033[0;31m Something went wrong with memory allocation \
\033[0m\n"
# define ERR_OPEN "❌\033[0;31m The file couldn't be opened \033[0m\n"
# define ERR_DUP "❌\033[0;31m Bad file descriptor \033[0m\n"
# define ERR_UNDEF "❌\033[0;31m Undefined error \033[0m\n"

typedef enum e_err_codes
{
	E_ARGS = -1,
	E_QUOTES = -2,
	E_MEM = -3,
	E_REDIR = -4,
	E_PIPE = -5,
	E_REDIR_IN = -6,
	E_REDIR_HD = -7,
	E_REDIR_OUT = -8,
	E_REDIR_OUT_T = -9,
	E_OPEN = -10,
	E_DUP = -11
}	t_err_codes;

#endif