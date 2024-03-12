/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/12 22:41:28 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_get_substr_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_count_substrs(char const *str, char c)
{
	int		counter;
	char	quote;

	counter = 0;
	while (*str)
	{
		if (*str != c && *str != SINGLE_Q && *str != DOUBLE_Q)
		{
			counter++;
			str += ft_get_substr_len(str, c);
		}
		else if (*str == SINGLE_Q || *str == DOUBLE_Q)
		{
			counter++;
			quote = *str;
			str += ft_get_substr_len(str, quote);
			if (*str == '\0')
				return (-1);
		}
		else
			str++;
	}
	return (counter);
}

static void	*free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs[i])
		free(substrs[i++]);
	free(substrs);
	return (NULL);
}

char	**ft_tokenizer(char const *s, char c)
{
	char	**substrs;
	int		nb_substr;
	char	quote;
	int		i;

	if (!s)
		return (NULL);
	nb_substr = ft_count_substrs(s, c);
	printf("nombre de mots : %i \n", nb_substr);
	if (nb_substr < 0)
		return (NULL);
	substrs = (char **)malloc((nb_substr + 1) * sizeof(char *));
	if (!substrs)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c && *s != SINGLE_Q && *s != DOUBLE_Q)
		{
			substrs[i] = ft_substr(s, 0, ft_get_substr_len(s, c));
			if (!substrs[i++])
				return (free_substrs(substrs));
			s += ft_get_substr_len(s, c);
		}
		else if (*s == SINGLE_Q || *s == DOUBLE_Q)
		{
			quote = *s;
			substrs[i] = ft_substr(s, 0, ft_get_substr_len(s, quote));
			if (!substrs[i++])
				return (free_substrs(substrs));
			s += ft_get_substr_len(s, quote);
		}
		else
			s++;
	}
	substrs[nb_substr] = NULL;
	return (substrs);
}
