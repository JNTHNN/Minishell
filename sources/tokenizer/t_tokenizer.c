/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/13 17:02:02 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


bool	ft_is_quote(char c)
{
	if (c == DBL_Q || c == SGL_Q)
		return (true);
	return (false);
}

int	ft_count_tokens(char *input)
{
	int		count;
	int		quote_char;
	bool	in_quotes;

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
				count++;
			}
			else if (*input == quote_char)
				in_quotes = false;
			input++;
			continue ;
		}
		if (!in_quotes && *input != SP)
		{
			count++;
			while (*input && *input != SP && !ft_is_quote(*input))
				input++;
		}
		else if (*input == SP)
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
	if (in_quotes)
		return (-1);
	return (count);
}

t_ast_node	*ft_tokenize(char *input)
{
	int	tok_nb;

	tok_nb = ft_count_tokens(input);
	printf("nb of tokens = %i\n", tok_nb);
	return (NULL);
}
