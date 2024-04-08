/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/08 23:11:40 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_calculate_new_length(char *str, char **env)
{
	int		i;
	int		len;
	char	*var_name;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && ft_should_expand_var(str, &str[i]))
		{
			var_name = ft_get_var_name(&str[i + 1]);
			len += ft_strlen(ft_get_env_value(env, var_name));
			while (str[i + 1] && (!ft_is_space(str[i + 1]) 
					&& !ft_is_quote(str[i + 1]) && str[i + 1] != DOLLAR))
				i++;
			free(var_name);
		}
		else
			len++;
		i++;
	}
	ft_adjust_length_for_quotes(str, &len);
	return (len);
}

size_t	ft_space_left(size_t buffsize, char *cursor, char *start)
{
	return (buffsize - (cursor - start) - 1);
}

void	ft_create_new_str(char *old, char *new, char **env, size_t buffsize)
{
	char			*cursor;
	static bool		state[2] = {false, false};
	char			*var[2];

	cursor = new;
	while (*old)
	{
		if (*old == DOLLAR && !state[IN_SGL_Q])
		{
			var[NAME] = ft_get_var_name(old + 1);
			var[VAL] = ft_get_env_value(env, var[NAME]);
			ft_strlcpy(cursor, var[VAL], ft_space_left(buffsize, cursor, new));
			cursor += ft_strlen(var[VAL]);
			old += ft_strlen(var[NAME]);
			free(var[NAME]);
		}
		else if (*old == SGL_Q && !state[IN_DBL_Q])
			state[IN_SGL_Q] = !state[IN_SGL_Q];
		else if (*old == DBL_Q && !state[IN_SGL_Q])
			state[IN_DBL_Q] = !state[IN_DBL_Q];
		else
			*cursor++ = *old;
		old++;
	}
	*cursor = '\0';
}

int	ft_handle_expansion(char ***args, int idx, char **env)
{
	char	*str;
	char	*new_str;
	char	*cursor;
	int		new_length;

	str = (*args)[idx];
	if (ft_count_all_quotes(str) || ft_count_dollars(str))
	{
		new_length = ft_calculate_new_length(str, env);
		new_str = (char *)malloc(new_length + 1);
		if (!new_str)
			return (E_MEM);
		cursor = new_str;
		ft_create_new_str(str, cursor, env, (new_length + 2));
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
			ret = ft_handle_expansion(&args, i, data->env);
			if (ret)
				return (ret);
			i++;
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
