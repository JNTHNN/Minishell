/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/22 13:26:27 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "❌\033[0;31m  Minishell doesn't accept arguments \033[0m\n"
# define ERR_QUOTES "❌\033[0;31m Unexpected token : unclosed quote \033[0m\n"
# define ERR_PIPE "❌\033[0;31m parse error near '|' \033[0m\n"
# define ERR_MEM "❌\033[0;31m Something went wrong with memory allocation \
\033[0m\n"

typedef enum e_err_codes
{
	E_ARGS = -1,
	E_QUOTES = -2,
	E_PIPE = -3,
	E_MEM = -4
}	t_err_codes;

#endif