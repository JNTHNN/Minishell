/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/08 22:01:35 by gdelvign         ###   ########.fr       */
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

bool	ft_is_valid_variable_char(char c)
{
	if (ft_isalpha(c) || c == UNDERSCORE)
		return (true);
	return (false);
}

char	*ft_get_env_value(char **env, char *var_name)
{
	int		i;
	char	*var_value;

	var_value = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name)))
			var_value = ft_strchr(env[i], '=') + 1;
		i++;
	}
	return (var_value);
}

char	*ft_get_var_name(char *str)
{
	char	*start;

	start = str;
	if (*str == '\0' || ft_is_space(*str) || !ft_is_valid_variable_char(*str))
		return (NULL);
	while (*str && (!ft_is_space(*str)
			&& !ft_is_quote(*str) && *str != DOLLAR))
		str++;
	return (ft_substr(start, 0, str - start));
}

void	ft_adjust_length_for_quotes(char *str, int *length)
{
	bool	in_dbl_q;
	bool	in_sgl_q;

	in_sgl_q = false;
	in_dbl_q = false;
	while (*str)
	{
		if (*str == SGL_Q)
			in_sgl_q = !in_sgl_q;
		if (*str == DBL_Q)
			in_dbl_q = !in_dbl_q;
		if (*str == SGL_Q && !in_dbl_q)
			(*length)--;
		if (*str == DBL_Q && !in_sgl_q)
			(*length)--;
		str++;
	}
}

bool	ft_should_expand_var(char *str, char *chr)
{
	bool	in_dbl_q;
	bool	in_sgl_q;

	in_dbl_q = false;
	in_sgl_q = false;
	while (*str != *chr)
	{
		if (*str == DBL_Q && !in_sgl_q)
			in_dbl_q = !in_dbl_q;
		if (*str == SGL_Q && !in_dbl_q)
			in_sgl_q = !in_sgl_q;
		str++;
	}
	if ((!ft_count_all_quotes(str) || !ft_count_sgl_quotes(str)
			|| ((in_dbl_q && !in_sgl_q))))
		return (true);
	return (false);
}

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
	int			i;
	char		*var_name;
	char		*var_value;
	bool		in_dbl_q;
	bool		in_sgl_q;
	char 		*cursor;

	cursor = new;
	in_sgl_q = false;
	in_dbl_q = false;
	i = -1;
	while (old[++i])
	{
		if (old[i] == DOLLAR && ft_should_expand_var(old, &old[i]))
		{
			var_name = ft_get_var_name(&old[i + 1]);
			var_value = ft_get_env_value(env, var_name);
			ft_strlcpy(cursor, var_value, ft_space_left(buffsize, cursor, new));
			cursor += ft_strlen(var_value);
			i += ft_strlen(var_name);
			free(var_name);
		}
		else if (old[i] == SGL_Q && !in_dbl_q)
			in_sgl_q = !in_sgl_q;
		else if (old[i] == DBL_Q && !in_sgl_q)
			in_dbl_q = !in_dbl_q;
		else
			*cursor++ = old[i];
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
