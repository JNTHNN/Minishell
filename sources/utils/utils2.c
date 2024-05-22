/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:24:41 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/22 12:46:14 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	**ft_add_to_env(char **env, char *new_var)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup(env[j]);
		j++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	ft_free_array(env);
	return (new_env);
}

char	*ft_getenv(t_data *data, char *search)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		if (!ft_strncmp(data->env[i], search, ft_strlen(search)))
			return (data->env[i]);
		i++;
	}
	return (NULL);
}
