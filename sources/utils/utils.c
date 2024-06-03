/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:37:03 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/03 12:34:29 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees a dynamically allocated array of strings
** and sets the pointer to NULL.
*/
void	*ft_free_array(char **arr)
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

/*
** Creates a minimal environment array with PWD, SHLVL, and /usr/bin/env.
*/
char	**ft_create_env(char **arr)
{
	char	temp[PATH_MAX];

	arr = (char **)malloc(5 * sizeof(char *));
	if (!arr)
		return (NULL);
	if (getcwd(temp, sizeof(temp)))
		arr[0] = ft_strjoin(PWD, temp);
	arr[1] = ft_strdup("SHLVL=1");
	arr[2] = ft_strdup("_=/usr/bin/env");
	arr[3] = ft_strdup("OLDPWD");
	arr[4] = NULL;
	return (arr);
}

/*
** Copies an existing environment array,
** or create a new one if the input is NULL.
*/
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
	cpy = malloc((i + 2) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		cpy[i] = ft_strdup(arr[i]);
		if (!cpy[i])
			return (ft_free_array(cpy));
	}
	cpy[i] = ft_strdup("OLDPWD");
	cpy[i + 1] = NULL;
	return (cpy);
}
