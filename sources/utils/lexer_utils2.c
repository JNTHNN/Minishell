/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:07:25 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/19 15:10:52 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_quote(char c)
{
	if (c == DBL_Q || c == SGL_Q)
		return (true);
	return (false);
}

bool	ft_is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	ft_is_operator(char c)
{
	if (c == REDIR_IN || c == REDIR_OUT || c == PIPE)
		return (true);
	return (false);
}

int	ft_skip_whitespaces(char *str)
{
	char	*start;

	start = str;
	while (ft_is_space(*str))
		str++;
	return (str - start);
}

void	ft_trim_input(char **input)
{
	char	*trimmed;

	trimmed = ft_strtrim(*input, " ");
	if (trimmed)
	{
		free(*input);
		*input = trimmed;
	}
	else
		ft_throw_error(0, "TRIM ERROR");
}
