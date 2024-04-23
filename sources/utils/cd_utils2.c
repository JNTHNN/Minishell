/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:04:06 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/10 19:21:27 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_remove_first(char **path)
{
	char	**new_path;
	int		i;
	int		j;

	i = ft_tablen(path);
	new_path = (char **)malloc(i * sizeof(char *));
	if (!new_path)
		return (NULL);
	j = 1;
	while (j < i)
	{
		new_path[j - 1] = ft_strdup(path[j]);
		j++;
	}
	new_path[i - 1] = NULL;
	return (new_path);
}

char	**ft_append_pwd(char **pwd, char *path)
{
	int		i;
	char	**append_pwd;

	i = 0;
	append_pwd = (char **)malloc(sizeof(char *) * ft_tablen(pwd) + 2);
	if (!append_pwd)
		return (NULL);
	while (pwd && pwd[i])
	{
		append_pwd[i] = ft_strdup(pwd[i]);
		i++;
	}
	append_pwd[i] = ft_strdup(path);
	append_pwd[i + 1] = NULL;
	return (append_pwd);
}

char	**ft_replace_pwd(t_data *data, char *shortcut)
{
	char	*temp_pwd;
	char	**pwd;

	if (shortcut && !ft_strncmp(shortcut, "-", 1))
	{
		temp_pwd = ft_getenv(data, "OLDPWD=");
		printf("%s\n", temp_pwd + 7);
	}
	else
		temp_pwd = ft_getenv(data, "HOME=");
	pwd = ft_split(temp_pwd, '/');
	return (pwd);
}

char	**ft_sup_pwd(char **pwd)
{
	char	**new_pwd;
	int		len;
	int		i;

	i = 0;
	len = ft_tablen(pwd);
	new_pwd = (char **)malloc(sizeof(char *) * (ft_tablen(pwd)));
	if (!new_pwd)
		return (NULL);
	while (i < len - 1)
	{
		new_pwd[i] = ft_strdup(pwd[i]);
		i++;
	}
	new_pwd[i] = NULL;
	return (new_pwd);
}

char	*ft_pwdcat(char **pwd)
{
	char	*new_pwd;
	int		i;
	int		size;

	size = ft_tablen(pwd);
	i = 1;
	new_pwd = ft_strdup("");
	while (i < size)
	{
		new_pwd = ft_strjoin(new_pwd, "/");
		new_pwd = ft_strjoin(new_pwd, pwd[i]);
		i++;
	}
	return (new_pwd);
}
