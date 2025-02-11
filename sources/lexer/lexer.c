/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:14:03 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Stores an operator token from the input string into the token list.
*/
static int	ft_store_operator(t_data *data, char *str, int *token_nb)
{
	char	*token;
	int		length;

	length = 0;
	if ((*str == REDIR_IN && *(str + 1) == REDIR_IN)
		|| (*str == REDIR_OUT && *(str + 1) == REDIR_OUT))
		length = 2;
	else
		length = 1;
	token = ft_substr(str, 0, length);
	if (!token || ft_add_tok_node(token, ++(*token_nb), OPERATOR, data))
	{
		free(token);
		return (E_MEM);
	}
	return (length);
}

/*
** Stores a word token from the input string into the token list.
*/
static int	ft_store_word(t_data *data, char *str, int *token_nb)
{
	char	quote_char;
	char	*start;
	char	*token;

	start = str;
	quote_char = 0;
	while (*str && !ft_is_operator(*str))
	{
		ft_handle_quoted_word(&str, &quote_char);
		if (ft_is_space(*str))
			break ;
	}
	token = ft_substr(start, 0, str - start);
	if (!token || ft_add_tok_node(token, ++(*token_nb), WORD, data))
	{
		free(token);
		return (E_MEM);
	}
	return (str - start);
}

/*
** Extracts tokens from the input string and stores them in the token list.
*/
static int	ft_get_tokens(t_data *data)
{
	char	*str;
	int		token_nb;
	int		ret;

	token_nb = 0;
	str = data->input;
	while (*str)
	{
		str += ft_skip_whitespaces(str);
		if (ft_is_operator(*str))
		{
			ret = ft_store_operator(data, str, &token_nb);
			if (ret < 0)
				return (ret);
			str += ret;
		}
		else
		{
			ret = ft_store_word(data, str, &token_nb);
			if (ret < 0)
				return (ret);
			str += ret;
		}
	}
	return (EXIT_SUCCESS);
}

/*
** Checks if the input string has balanced quotes.
*/
int	ft_check_quotes(char *input)
{
	int		quote_char;
	bool	in_quotes;

	quote_char = 0;
	in_quotes = false;
	while (*input)
	{
		if (ft_is_quote(*input))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_char = *input;
			}
			else if (*input == quote_char)
				in_quotes = false;
		}
		input++;
	}
	if (in_quotes)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** Tokenizes the input string and checks for syntax errors.
*/
int	ft_tokenize(t_data *data)
{
	if (ft_check_quotes(data->input))
		return (E_QUOTES);
	if (ft_get_tokens(data))
		return (E_MEM);
	if (ft_check_pipes(data->tokens))
		return (E_PIPE);
	free(data->input);
	data->input = NULL;
	return (EXIT_SUCCESS);
}
