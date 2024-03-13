/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/13 12:13:05 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_tokens(char *input)
{
	int		count;
	int		in_quotes;
	int		quote_char;
	char	*start_of_input;

	count = 0;
	in_quotes = false;
	quote_char = 0;
	start_of_input = input;
	printf("tu es ici\n");
	while (*input)
	{
		
	}
	if (in_quotes)
		return (-1);
	printf("tu es là\n");
	return (count);
}

t_ast_node	*ft_tokenize(char *input)
{
	int	tok_nb;

	tok_nb = ft_count_tokens(input);
	printf("nb of tokens = %i\n", tok_nb);
	return (NULL);
}
