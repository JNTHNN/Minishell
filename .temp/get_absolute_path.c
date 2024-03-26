/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:44:24 by jonathang         #+#    #+#             */
/*   Updated: 2024/01/05 13:17:08 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    get_absolute_path(char *cmd, char **env)
{
    char	*path;
    char	**path_split;
    char	*tmp;
    int		i;

    i = 0;
    path = ft_strdup(getenv("PATH"));
    path_split = ft_split(path, ':');
    while (path_split[i])
    {
        tmp = ft_strjoin(path_split[i], "/");
        tmp = ft_strjoin(tmp, cmd);
        if (access(tmp, F_OK) == 0)
        {
            execve(tmp, env, NULL);
            break ;
        }
        i++;
    }
}
