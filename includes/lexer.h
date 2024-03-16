/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:39:02 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/16 22:50:20 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum e_quotes_char
{
	DBL_Q = 34,
	SGL_Q = 39
};

enum e_redirect_op
{
	REDIR_IN = '<',
	REDIR_OUT = '>',
	PIPE_OP = '|'
};

#endif
