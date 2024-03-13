/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/13 15:38:58 by gdelvign         ###   ########.fr       */
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
	char	*input_start;

	count = 0;
	quote_char = 0;
	input_start = input;
	while (*input)
	{
		if (ft_is_quote(*input))
		{
			quote_char = *input;
			if (input == input_start || *(input - 1) == SP)
				count++;
			input++;
			while (*input && *input != quote_char)
				input++;
			if (*input == EOS)
				return (-1);
			if (*input == quote_char)
			{
				if (*(input + 1) == EOS)
					input++;
				else
				{
					quote_char = 0;
					input++;
				}
			}
		}
		else if (*input != SP)
		{
			count++;
			while (*input && *input != SP)
				input++;
		}
		else
			input++;
	}
	return (count);
}

t_ast_node	*ft_tokenize(char *input)
{
	int	tok_nb;

	tok_nb = ft_count_tokens(input);
	printf("nb of tokens = %i\n", tok_nb);
	return (NULL);
}
