/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:07:25 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/26 22:17:03 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if the given character is a quote (single or double).
*/
bool	ft_is_quote(char c)
{
	if (c == DBL_Q || c == SGL_Q)
		return (true);
	return (false);
}

/*
** Checks if the given character is a whitespace character.
*/
bool	ft_is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/*
** Checks if the given character is an operator (redirection or pipe).
*/
bool	ft_is_operator(char c)
{
	if (c == REDIR_IN || c == REDIR_OUT || c == PIPE)
		return (true);
	return (false);
}

/*
** Skips over any whitespace characters in the given string.
*/
int	ft_skip_whitespaces(char *str)
{
	char	*start;

	start = str;
	while (ft_is_space(*str))
		str++;
	return (str - start);
}

/*
** Trims leading and trailing whitespace from the input string.
*/
int	ft_trim_input(char **input)
{
	char	*trimmed;

	trimmed = ft_strtrim(*input, " ");
	if (trimmed != NULL)
	{
		free(*input);
		*input = trimmed;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
