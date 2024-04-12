/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:40:52 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 16:44:43 by gdelvign         ###   ########.fr       */
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

void	ft_increment(int *idx, int *len)
{
	(*idx)++;
	(*len)++;
}

void	ft_get_var_val_length(t_data *data, char **str, int *i, int *len)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_get_var_name(&(*str)[*i + 1]);
	if (var_name && *var_name)
	{
		if (!ft_strncmp(var_name, "?", ft_strlen(var_name)))
		{
			var_value = ft_itoa(exit_code);
			data->is_itoa = true;
		}
		else
			var_value = ft_get_env_value(data->env, var_name);
		*i += ft_strlen(var_name);
		*len += ft_strlen(var_value);
		free(var_name);
		if (data->is_itoa)
		{
			free(var_value);
			data->is_itoa = false;
		}
	}
	else
		ft_increment(i, len);
}
