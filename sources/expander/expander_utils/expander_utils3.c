/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:40:52 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/03 08:29:20 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if characters of the variable name are valid or not.
*/
bool	ft_is_valid_var_char(char c)
{
	return (c == '?' || c == '_' || ft_isalnum(c) || ft_is_quote(c));
}

/*
** Wins some lines of code by incrementing both values in the same time.
*/
void	ft_increment(int *idx, int *len)
{
	(*idx)++;
	(*len)++;
}

/*
** Gets the legnth of the environment variable before expansion.
*/
void	ft_get_var_val_length(t_data *data, char **str, int *i, int *len)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_get_var_name(&(*str)[*i + 1]);
	if (var_name && *var_name)
	{
		if (!ft_strncmp(var_name, "?", ft_strlen(var_name)))
		{
			var_value = ft_itoa(g_exit_code);
			data->is_itoa = true;
		}
		else
			var_value = ft_get_env_value(data->env, var_name);
		*i += ft_strlen(var_name) + 1;
		if (var_value)
			*len += ft_strlen(var_value);
		free(var_name);
		if (var_value && data->is_itoa)
		{
			free(var_value);
			data->is_itoa = false;
		}
	}
	else
		(*i)++;
}

/*
** Finds the value of the environment variable,
** copies it in the new expqnded string. 
*/
void	ft_create_var_val(t_data *data, char **str, char **cursor,
			size_t space_left)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_get_var_name(*str);
	if (var_name && *var_name)
	{
		if (!ft_strncmp(var_name, "?", ft_strlen(var_name)))
		{
			var_value = ft_itoa(g_exit_code);
			data->is_itoa = true;
		}
		else
			var_value = ft_get_env_value(data->env, var_name);
		ft_strlcpy(*cursor, var_value, space_left);
		*cursor += ft_strlen(var_value);
		*str += ft_strlen(var_name);
		if (data->is_itoa)
		{
			free(var_value);
			data->is_itoa = false;
		}
	}
	else
		**cursor++ = '$';
	free(var_name);
}

/*
** Skips quotes in calculation if necessary and copies characters.
*/
void	ft_process_character(char **old, char **cursor, bool state[2])
{
	if (**old == SGL_Q && !state[IN_DBL_Q])
	{
		state[IN_SGL_Q] = !state[IN_SGL_Q];
		(*old)++;
	}
	else if (**old == DBL_Q && !state[IN_SGL_Q])
	{
		state[IN_DBL_Q] = !state[IN_DBL_Q];
		(*old)++;
	}
	else
		*(*cursor)++ = *(*old)++;
}
