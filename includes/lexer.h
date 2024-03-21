/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:39:02 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/21 12:41:34 by gdelvign         ###   ########.fr       */
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
	PIPE = '|'
};

/* Lexer utils to handle the storing of tokens : lexer_utils2.c */
bool	ft_is_quote(char c);
bool	ft_is_space(int c);
bool	ft_is_operator(char c);
int		ft_skip_whitespaces(char *str);
int		ft_trim_input(char **input);

/* Lexer utils to handle the storing of tokens : lexer_utils3.c */
void	ft_handle_quoted_word(char **str, char *quote_c);

#endif
