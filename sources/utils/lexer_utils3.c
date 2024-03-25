/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:56:26 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/25 16:20:00 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_quoted_word(char **str, char *quote_c)
{
	if (ft_is_quote(**str))
	{
		quote_c = *str;
		(*str)++;
		while (**str && **str != *quote_c)
			(*str)++;
		if (**str == *quote_c)
			(*str)++;
	}
	else
		(*str)++;
}

bool	ft_check_pipes(t_tok_lst *lst)
{
	t_tok_lst	*last;

	last = ft_tok_lstlast(lst);
	if ((lst->type == OPERATOR && lst->token[0] == PIPE)
		|| (last->type == OPERATOR && last->token[0] == PIPE))
		return (true);
	return (false);
}

t_redirect_type	ft_find_redir_type(char *token, t_tok_type type)
{
	size_t	size;

	if (type == OPERATOR)
	{
		size = ft_strlen(token);
		if (token[0] == PIPE)
			return (R_PIPE);
		else if (token[0] == REDIR_IN)
		{
			if (size == 2)
				return (HEREDOC);
			return (IN);
		}
		else
		{
			if (size == 2)
				return (OUT_T);
			return (OUT);
		}
	}
	return (0);
}
