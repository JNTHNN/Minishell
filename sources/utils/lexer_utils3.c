/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:56:26 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/19 17:10:16 by gdelvign         ###   ########.fr       */
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
