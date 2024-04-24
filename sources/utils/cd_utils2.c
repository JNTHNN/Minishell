/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:04:06 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/23 22:18:35 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	removes the first path from the path
*/
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

/*
**	adds the path to the end
*/
char	**ft_append_pwd(char **pwd, char *path)
{
	int		i;
	char	**append_pwd;

	i = 0;
	append_pwd = (char **)malloc(sizeof(char *) * ft_tablen(pwd) + 2);
	if (!append_pwd)
		return (NULL);
	while (pwd[i])
	{
		append_pwd[i] = ft_strdup(pwd[i]);
		i++;
	}
	append_pwd[i] = ft_strdup(path);
	append_pwd[i + 1] = NULL;
	return (append_pwd);
}

/*
**	replaces the shortcut with the corresponding path
*/
char	**ft_replace_pwd(t_data *data, char *shortcut)
{
	char	*temp_pwd;
	char	**pwd;

	temp_pwd = NULL;
	if (shortcut && !ft_strncmp(shortcut, "-", 1))
	{
		temp_pwd = ft_getenv(data, "OLDPWD=");
		if (temp_pwd)
			printf("%s\n", temp_pwd + 7);
	}
	else
		temp_pwd = ft_getenv(data, "HOME=");
	pwd = ft_split(temp_pwd, '/');
	return (pwd);
}

/*
**	removes the ".." from the path
*/
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
	ft_free_array(pwd);
	return (new_pwd);
}

/*
**	concat pwd for relative
*/
char	*ft_pwdcat(char **pwd)
{
	char	*new_pwd;
	char	*temp;
	int		i;
	int		size;

	size = ft_tablen(pwd);
	i = 0;
	new_pwd = ft_strdup("");
	while (i < size)
	{
		temp = ft_strjoin(new_pwd, "/");
		free(new_pwd);
		new_pwd = ft_strjoin(temp, pwd[i]);
		i++;
	}
	return (new_pwd);
}
