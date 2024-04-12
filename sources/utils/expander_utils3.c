/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:40:52 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 10:47:01 by gdelvign         ###   ########.fr       */
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

bool	ft_is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
