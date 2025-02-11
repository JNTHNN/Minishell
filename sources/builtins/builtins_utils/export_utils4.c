/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:42:31 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/29 10:40:30 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	strdup with size parameter
*/
static char	*ft_strndup(char *s1, int size)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
**	Check if the env var name content letter/number/equal | return false if not
*/
bool	ft_is_valid_var_name(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == 61 || c == 95)
		return (true);
	return (false);
}

/*
**	extract the var name from string
*/
char	*ft_var(char *s)
{
	char	*equal_sign;
	int		size;
	char	*var;

	var = NULL;
	equal_sign = ft_strchr(s, '=');
	if (equal_sign)
	{
		size = equal_sign - s + 1;
		var = ft_strndup(s, size);
		return (var);
	}
	return (ft_strdup(s));
}

/*
**	extract the data from string
*/
char	*ft_data(char *s)
{
	char	*equal_sign;
	char	*data;
	int		start;

	data = NULL;
	equal_sign = ft_strchr(s, '=');
	if (equal_sign)
	{
		start = equal_sign - s + 1;
		data = ft_strdup(s + start);
	}
	return (data);
}
