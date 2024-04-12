/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 15:23:43 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_calculate_new_length(char *str, t_data *data)
{
	int		i;
	int		len;
	char	*var_name;
	char	*var_value;
	bool	is_itoa;
	char	*start;

	start = str;
	is_itoa = false;
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && ft_should_expand_var(start, &str[i]))
		{
			if (str[i + 1] == '\0' || ft_is_space(str[i + 1])
				|| !ft_is_valid_var_char(str[i + 1]))
			{
				len++;
				i++;
				continue ;
			}
			var_name = ft_get_var_name(&str[i + 1]);
			if (var_name && *var_name)
			{
				if (!ft_strncmp(var_name, "?", ft_strlen(var_name)))
				{
					var_value = ft_itoa(exit_code);
					is_itoa = true;
				}
				else
					var_value = ft_get_env_value(data->env, var_name);
				i += ft_strlen(var_name);
				len += ft_strlen(var_value);
				free(var_name);
				if (is_itoa)
					free(var_value);
			}
			else
			{
				len++;
				i++;
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	ft_adjust_length_for_quotes(str, &len);
	return (len);
}

size_t	ft_space_left(size_t buffsize, char *cursor, char *start)
{
	return (buffsize - (cursor - start) - 1);
}

void	ft_create_new_str(char *old, char *new, t_data *data, size_t buffsize)
{
	char			*cursor;
	static bool		state[2] = {false, false};
	char			*var[2];
	bool			is_itoa;

	is_itoa = false;
	cursor = new;
	while (*old)
	{
		if (*old == DOLLAR && !state[IN_SGL_Q])
		{
			old++;
			if (*old == '\0' || ft_is_space(*old)
				|| !ft_is_valid_var_char(*old))
				*cursor++ = '$';
			else
			{
				var[NAME] = ft_get_var_name(old);
				if (var[NAME] && *var[NAME])
				{
					if (!ft_strncmp(var[NAME], "?", ft_strlen(var[NAME])))
					{
						var[VAL] = ft_itoa(exit_code);
						is_itoa = true;
					}
					else
						var[VAL] = ft_get_env_value(data->env, var[NAME]);
					ft_strlcpy(cursor, var[VAL], ft_space_left(buffsize, cursor, new));
					cursor += ft_strlen(var[VAL]);
					old += ft_strlen(var[NAME]);
					if (is_itoa)
						free(var[VAL]);
				}
				else
					*cursor++ = '$';
				free(var[NAME]);
			}
		}
		else if (*old == SGL_Q && !state[IN_DBL_Q])
		{
			state[IN_SGL_Q] = !state[IN_SGL_Q];
			old++;
		}
		else if (*old == DBL_Q && !state[IN_SGL_Q])
		{
			state[IN_DBL_Q] = !state[IN_DBL_Q];
			old++;
		}
		else
			*cursor++ = *old++;
	}
	*cursor = '\0';
}

int	ft_handle_expansion(char ***args, int idx, t_data *data)
{
	char	*str;
	char	*new_str;
	char	*cursor;
	int		new_length;

	str = (*args)[idx];
	if (ft_count_all_quotes(str) || ft_count_dollars(str))
	{
		new_length = ft_calculate_new_length(str, data);
		new_str = (char *)malloc(new_length + 1);
		if (!new_str)
			return (E_MEM);
		cursor = new_str;
		ft_create_new_str(str, cursor, data, (new_length + 2));
		free((*args)[idx]);
		(*args)[idx] = new_str;
		printf("FINAL = %s\n", (*args)[idx]);
	}
	return (EXIT_SUCCESS);
}

int	ft_expand(t_data *data)
{
	t_cmd	*current;
	char	**args;
	int		i;
	int		ret;

	current = data->cmd;
	while (current)
	{
		args = current->args;
		i = 0;
		while (args[i])
		{
			ret = ft_handle_expansion(&args, i, data);
			if (ret)
				return (ret);
			i++;
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
