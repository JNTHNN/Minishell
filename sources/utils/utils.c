/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:37:03 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 21:57:40 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

char	**ft_arrcpy(char **arr)
{
	int		i;
	char	**cpy;

	if (!arr || !arr[0])
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	cpy = malloc((i + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		cpy[i] = ft_strdup(arr[i]);
		if (!cpy[i])
			return (free_arr(cpy));
	}
	cpy[i] = NULL;
	return (cpy);
}

char	**ft_create_env(char **arr)
{
	char	temp[PATH_MAX];

	arr = (char **)malloc(4 * sizeof(char *));
	if (!arr)
		return (NULL);
	if (getcwd(temp, sizeof(temp)))
		arr[0] = ft_strjoin("PWD=", temp);
	arr[1] = ft_strdup("SHLVL=1");
	arr[2] = ft_strdup("/usr/bin/env");
	arr[3] = NULL;
	return (arr);
}

char	**ft_envcpy(char **arr)
{
	int		i;
	char	**cpy;

	cpy = NULL;
	if (!arr || !arr[0])
		return (ft_create_env(cpy));
	i = 0;
	while (arr[i])
		i++;
	cpy = malloc((i + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		cpy[i] = ft_strdup(arr[i]);
		if (!cpy[i])
			return (free_arr(cpy));
	}
	cpy[i] = NULL;
	return (cpy);
}
