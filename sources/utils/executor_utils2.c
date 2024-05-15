/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:08:36 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/15 11:13:11 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_pathiter(char **path, t_cmd *cmd)
{
	char	*new_cmd;
	char	*temp;

	new_cmd = ft_strjoin("/", cmd->args[0]);
	while (path && *path)
	{
		temp = ft_strjoin(*path, new_cmd);
		*path = temp;
		path++;
	}
	return (path);
}

char	**ft_path_abs(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**my_path;

	path = ft_getenv(data, "PATH");
	my_path = ft_split(path, ':');
	ft_pathiter(my_path, cmd);
	return (my_path);
}
