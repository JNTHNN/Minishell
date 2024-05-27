/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:56:26 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/19 10:06:34 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles quoted words in the string,
advancing the pointer past the quoted section.
*/
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

/*
** Checks for improper pipe usage, such as pipes
at the start, end, or consecutive pipes.
*/
bool	ft_check_pipes(t_tok_lst *lst)
{
	t_tok_lst	*last;
	t_tok_lst	*prev;

	last = ft_tok_lstlast(lst);
	if (lst->r_type == R_PIPE || last->r_type == R_PIPE)
		return (true);
	while (lst != NULL)
	{
		prev = lst;
		lst = lst->next;
		if (prev->r_type == R_PIPE && lst->r_type == R_PIPE)
			return (true);
	}
	return (false);
}

/*
** Determines the type of redirection based on the token and its type.
*/
t_redirect_type	ft_find_redir_type(char *token, t_tok_type type)
{
	size_t	size;

	if (token[0] && type == OPERATOR)
	{
		size = ft_strlen(token);
		if (size == 1 && token[0] == PIPE)
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
