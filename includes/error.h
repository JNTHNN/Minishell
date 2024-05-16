/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 11:56:50 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "❌\033[0;31m  Minishell doesn't accept arguments \033[0m\n"
# define ERR_QUOTES "❌\033[0;31m Unexpected token : unclosed quote \033[0m\n"
# define ERR_REDIR "❌\033[0;31m Syntax error near unexpected token "
# define ERR_MEM "❌\033[0;31m readline: out of virtual memory \033[0m\n"
# define ERR_OPEN " No such file or directory\033[0m\n"
# define ERR_DUP "❌\033[0;31m Bad file descriptor \033[0m\n"
# define ERR_FORK "❌\033[0;31m minibash: fork: Resource temporarily unavailable \
\033[0m\n"
# define ERR_OLDPWD "❌\033[0;31m minibash: cd: OLDPWD not set\033[0m\n"
# define ERR_HOME "❌\033[0;31m minibash: cd: HOME not set\033[0m\n"
# define ERR_VAR "❌\033[0;31m minibash: export: not valid in this context \
\033[0m\n"
# define ERR_VAR_ID "❌\033[0;31m minibash: export: not an identifier\033[0m\n"
# define ERR_VAR_EQ "❌\033[0;31m minibash: export: not a valid identifier \
\033[0m\n"
# define ERR_U_VAR "❌\033[0;31m minibash: unset: not valid in this context\
\033[0m\n"
# define ERR_U_VAR_ID "❌\033[0;31m minibash: unset: not an identifier\033[0m\n"
# define ERR_U_VAR_EQ "❌\033[0;31m minibash: unset: not a valid identifier \
\033[0m\n"
# define ERR_NUM_ARG ": numeric argument required\033[0m\n"
# define ERR_TOO_ARG "too many arguments\033[0m\n"
# define START_EXIT "❌\033[0;31mminibash: exit: "
# define ERR_UNDEF "❌\033[0;31m Undefined error \033[0m\n"
# define START_ERR "❌\033[0;31m minibash: "
# define ERR_CMD ": command not found\033[0m\n"
# define END_RST "\033[0m"

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
	E_DUP = -11,
	E_EXECVE = -12,
	E_DIR = -13,
	E_NOTF = -14,
	E_EXECVE_2 = -15,
	E_CLOSE = -16
}	t_err_codes;

/*		Handle errors : error.c		*/
int		ft_handle_error(t_data *data, int ret);

/*		Handle errors : error2.c		*/
void	ft_handle_arg_error(int argc, char **argv);
void	ft_errno(char *s, int code, t_data *data);

#endif