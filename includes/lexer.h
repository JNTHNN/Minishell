/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:39:02 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/30 21:49:03 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum e_redirect_op
{
	REDIR_IN = '<',
	REDIR_OUT = '>',
	PIPE = '|'
};

/* Lexer utils to handle the storing of tokens : lexer_utils.c */
t_tok_lst		*ft_tok_lstlast(t_tok_lst *lst);

/* Lexer utils to handle the storing of tokens : lexer_utils2.c */
bool			ft_is_quote(char c);
bool			ft_is_space(int c);
bool			ft_is_operator(char c);
int				ft_skip_whitespaces(char *str);
int				ft_trim_input(char **input);

/* Lexer utils to handle the storing of tokens : lexer_utils3.c */
void			ft_handle_quoted_word(char **str, char *quote_c);
bool			ft_check_pipes(t_tok_lst *lst);
t_redirect_type	ft_find_redir_type(char *token, t_tok_type type);

#endif
