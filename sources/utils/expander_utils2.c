/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:08:46 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 14:59:08 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env_value(char **env, char *var_name)
{
	int		i;
	char	*var_value;
	char	*new_var_name;

	var_value = NULL;
	if (!var_name)
		return (NULL);
	i = 0;
	new_var_name = ft_strjoin(var_name, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], new_var_name, ft_strlen(new_var_name)))
			var_value = ft_strchr(env[i], '=') + 1;
		i++;
	}
	free(new_var_name);
	return (var_value);
}

char	*ft_get_var_name(char *str)
{
	char	*start;

	start = str;
	if (*str == '?')
		return (ft_strdup("?"));
	else if (ft_is_not_valid_variable_char(*str))
		return (NULL);
	while (*str && !ft_is_not_valid_variable_char(*str))
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
	while (str != chr)
	{
		if (*str == DBL_Q && !in_sgl_q)
			in_dbl_q = !in_dbl_q;
		if (*str == SGL_Q && !in_dbl_q)
			in_sgl_q = !in_sgl_q;
		str++;
	}
	if (!ft_count_all_quotes(str) || !ft_count_sgl_quotes(str)
		|| !in_sgl_q)
		return (true);
	return (false);
}
