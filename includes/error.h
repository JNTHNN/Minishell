/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:31 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/16 22:27:48 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define PREFIX "❌\033[0;31m "
# define ERR_ARG "Minishell doesn't accept arguments\n"
# define ERR_QUOTES "Unexpected token : quote\n"

/* Handle errors : error.c */
void	ft_throw_error(int err_code, char *err_msg);

#endif