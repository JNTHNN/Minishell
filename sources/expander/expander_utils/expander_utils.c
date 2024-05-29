/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:04:15 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:08:40 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts the number of single quotes in the input.
*/
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

/*
** Counts the number of double quotes in the input.
*/
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

/*
** Counts the number of dollar sign in the input.
*/
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

/*
** Counts the number of all quotes (simple and double) in the input.
*/
int	ft_count_all_quotes(char *str)
{
	if (!str)
		return (0);
	return (ft_count_dbl_quotes(str) + ft_count_sgl_quotes(str));
}

/*
** Checks if the environment variable character is valid or not.
*/
bool	ft_is_not_valid_variable_char(char c)
{
	if (c == '\0' || ft_is_space(c) || ft_is_quote(c)
		|| c == DOLLAR || (!ft_isalnum(c) && c != UNDERSCORE))
		return (true);
	return (false);
}
