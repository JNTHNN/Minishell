/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:04:15 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/24 12:35:10 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_sgl_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == SGL_Q)
			i++;
		str++;
	}
	return (i);
}

int	ft_count_dbl_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == DBL_Q)
			i++;
		str++;
	}
	return (i);
}

int	ft_count_dollars(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == DOLLAR)
			i++;
		str++;
	}
	return (i);
}

int	ft_count_all_quotes(char *str)
{
	if (!str)
		return (0);
	return (ft_count_dbl_quotes(str) + ft_count_sgl_quotes(str));
}

bool	ft_is_not_valid_variable_char(char c)
{
	if (c == '\0' || ft_is_space(c) || ft_is_quote(c)
		|| c == DOLLAR || !ft_isalnum(c))
		return (true);
	return (false);
}
