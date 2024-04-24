/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:42:31 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/24 11:00:24 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char	*ft_if_quotes(char *s)
// {
// 	size_t	len;

// 	len = ft_strlen(s);
// 	if (ft_is_quote(s[0]) && ft_is_quote(s[len - 1]))
// 	{
// 		if (s[0] == SGL_Q)
// 			return ("\'");
// 		if (s[0] == DBL_Q)
// 			return ("\"");
// 	}
// 	return (NULL);
// }

// static void	ft_trim_quotes(char **s)
// {
// 	if (s && *s)
// 	{
// 		if (ft_if_quotes(*s))
// 			*s = ft_strtrim(*s, ft_if_quotes(*s));
// 	}
// }

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

char	*ft_data(char *s)
{
	char	*equal_sign;
	char	*data;
	int		start;

	data = NULL;
	equal_sign = ft_strrchr(s, '=');
	if (equal_sign)
	{
		start = equal_sign - s + 1;
		data = ft_strdup(s + start);
	}
	// ft_trim_quotes(&data);
	return (data);
}
