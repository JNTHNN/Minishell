/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:56:26 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/22 12:19:34 by gdelvign         ###   ########.fr       */
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
