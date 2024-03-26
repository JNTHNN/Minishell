/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/18 20:23:24 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "❌\033[0;31m  Minishell doesn't accept arguments \033[0m\n"
# define ERR_QUOTES "❌\033[0;31m Unexpected token : unclosed quote \033[0m\n"
# define ERR_MEM "❌\033[0;31m Something went wrong with memory allocation \033[0m\n"

/* Handle errors : error.c */
void	ft_throw_error(int err_code, char *err_msg);

#endif