/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:02:51 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/28 17:14:21 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_new_line(char *old, char *new, t_data *data, size_t buffsize)
{
	char			*cursor;
	size_t			space_left;

	cursor = new;
	while (*old)
	{
		if (*old == DOLLAR)
		{
			old++;
			if (!(*old) || ft_is_space(*old) || !ft_is_valid_var_char(*old))
				*cursor++ = '$';
			else
			{
				space_left = ft_space_left(buffsize, cursor, new);
				ft_create_var_val(data, &old, &cursor, space_left);
			}
		}
		else
			*cursor++ = *old++;
	}
	*cursor = '\0';
}

int	ft_calc_line_new_len(char *str, t_data *data)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR)
		{
			if (!(str[i + 1]) || ft_is_space(str[i + 1])
				|| !ft_is_valid_var_char(str[i + 1]))
				ft_increment(&i, &len);
			ft_get_var_val_length(data, &str, &i, &len);
		}
		else
			ft_increment(&i, &len);
	}
	return (len);
}
