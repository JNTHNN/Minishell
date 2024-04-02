/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:37:03 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/02 14:55:28 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

char	**ft_arrcpy(char **arr)
{
	int		i;
	char	**cpy;

	if (!arr || !arr[0])
	{
		printf("OK\n");
		cpy = malloc((2 + 1) * sizeof(char *));
		cpy[0] = ft_strdup("TEST=OUI");
		cpy[1] = ft_strdup("TEST2=COOL");
		cpy[2] = NULL;
		return (cpy);
	}
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
