/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:39:02 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:17:09 by jgasparo         ###   ########.fr       */
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

/*  lexer.c */
int				ft_check_quotes(char *input);
int				ft_tokenize(t_data *data);

/* Lexer utils to handle the storing of tokens : lexer_utils.c */
t_tok_lst		*ft_tok_lstlast(t_tok_lst *lst);
int				ft_add_tok_node(char *str, int id, t_tok_type type, \
								t_data *data);

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
