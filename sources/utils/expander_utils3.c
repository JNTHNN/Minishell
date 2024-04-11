/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:40:52 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/11 16:32:43 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_not_valid_variable_char(char c)
{
	if (c == '\0' || ft_is_space(c) || ft_is_quote(c)
		|| c == DOLLAR || !ft_isalnum(c))
		return (true);
	return (false);
}
