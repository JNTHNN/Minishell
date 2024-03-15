/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/15 17:15:38 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_quote(char c)
{
	if (c == DBL_Q || c == SGL_Q)
		return (true);
	return (false);
}

// static bool	ft_is_space(int c)
// {
// 	if (c == 32 || (c >= 9 && c <= 13))
// 		return (true);
// 	return (false);
// }

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

// int	ft_count_tokens(char *input)
// {
// 	int		count;
// 	int		quote_char;
// 	bool	in_quotes;

// 	count = 0;
// 	quote_char = 0;
// 	in_quotes = false;
// 	while (*input)
// 	{
// 		if (ft_is_quote(*input))
// 		{
// 			if (!in_quotes)
// 			{
// 				in_quotes = true;
// 				quote_char = *input;
// 				count++;
// 			}
// 			else if (*input == quote_char)
// 				in_quotes = false;
// 			input++;
// 			continue ;
// 		}
// 		if (!in_quotes && !ft_is_space(*input))
// 		{
// 			count++;
// 			while (*input && !ft_is_space(*input) && !ft_is_quote(*input))
// 				input++;
// 		}
// 		else if (ft_is_space(*input))
// 			input++;
// 		if (in_quotes)
// 		{
// 			while (*input && (*input != quote_char))
// 				input++;
// 			if (*input == quote_char)
// 			{
// 				in_quotes = false;
// 				input++;
// 			}
// 		}
// 	}
// 	if (in_quotes)
// 		return (-1);
// 	return (count);
// }

t_token_lst	*ft_tokenize(char *input)
{
	int	value;

	value = ft_check_quotes(input);
	printf("valid = %i\n", value);
	return (NULL);
}
