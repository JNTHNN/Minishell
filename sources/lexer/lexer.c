/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/16 23:12:49 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_quote(char c)
{
	if (c == DBL_Q || c == SGL_Q)
		return (true);
	return (false);
}

static bool	ft_is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

static bool	ft_is_operator(char c)
{
	if (c == REDIR_IN || c == REDIR_OUT || c == PIPE_OP)
		return (true);
	return (false);
}

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

/* TODO: count redirection operators as tokens  and refacto this function) */
int	ft_count_tokens(char *input)
{
	int		count;
	int		quote_char;
	bool	in_quotes;
	char 	*start; 

	start = input;
	count = 0;
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
				if (input == start
					|| (input > start && ft_is_space(*(input - 1))))
					count++;
			}
			else if (*input == quote_char)
				in_quotes = false;
			input++;
			continue ;
		}
		if (!in_quotes && ft_is_operator(*input))
		{
			count++;
			while (*input && ft_is_operator(*(input)))
				input++;
		}
		else if (!in_quotes && !ft_is_space(*input))
		{
			count++;
			while (*input && !ft_is_space(*input) && !ft_is_quote(*input)
				&& !ft_is_operator(*input))
				input++;
		}
		else if (ft_is_space(*input))
			input++;
		if (in_quotes)
		{
			while (*input && (*input != quote_char))
				input++;
			if (*input == quote_char)
			{
				in_quotes = false;
				input++;
			}
		}
	}
	return (count);
}

t_token_lst	*ft_tokenize(char *input)
{
	int				tok_nb;
	t_token_lst		*tokens;

	if (ft_check_quotes(input))
		ft_throw_error(0, ERR_QUOTES);
	tok_nb = ft_count_tokens(input);
	printf("nb of tokens = %i\n", tok_nb);
	if (tok_nb)
		tokens = (t_token_lst *)malloc(tok_nb * sizeof(t_token_lst));
	if (!tokens)
		return (NULL);
	return (NULL);
}
