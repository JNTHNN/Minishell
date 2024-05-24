/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:04:06 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/24 12:58:09 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	removes the first path from the path
*/
char	**ft_remove_first(char **path, t_cd *cd)
{
	char	**new_path;
	int		i;
	int		j;

	i = ft_tablen(path);
	new_path = (char **)malloc(i * sizeof(char *));
	if (!new_path)
		ft_errno(ERR_MEM, EX_MISCERROR, cd->data);
	j = 1;
	while (j < i)
	{
		new_path[j - 1] = ft_strdup(path[j]);
		j++;
	}
	new_path[i - 1] = NULL;
	ft_free_array(path);
	return (new_path);
}

/*
**	adds the path to the end
*/
char	**ft_append_pwd(int last, t_cd *cd)
{
	int		i;
	char	**append_pwd;

	i = 0;
	append_pwd = (char **)malloc(sizeof(char *)
			* (ft_tablen(cd->temp_pwd) + 2));
	if (!append_pwd)
		ft_errno(ERR_MEM, EX_MISCERROR, cd->data);
	while (cd->temp_pwd && cd->temp_pwd[i])
	{
		append_pwd[i] = ft_strdup(cd->temp_pwd[i]);
		i++;
	}
	append_pwd[i] = ft_strdup(cd->temp_path[last]);
	append_pwd[i + 1] = NULL;
	if (cd->temp_pwd)
		ft_free_array(cd->temp_pwd);
	return (append_pwd);
}

/*
**	replaces the shortcut with the corresponding path
*/
char	**ft_replace_pwd(t_cd *cd, char *shortcut)
{
	char	*temp_pwd;
	char	**pwd;

	if (shortcut && !ft_strncmp(shortcut, "-", 1))
	{
		temp_pwd = cd->oldpwd;
		if (temp_pwd)
			printf("%s\n", temp_pwd + 7);
	}
	else
		temp_pwd = cd->home;
	pwd = ft_split(temp_pwd, '/');
	free(temp_pwd);
	return (pwd);
}

/*
**	removes the ".." from the path
*/
char	**ft_sup_pwd(t_cd *cd)
{
	char	**new_pwd;
	int		len;
	char	*temp;
	int		i;

	i = 0;
	len = ft_tablen(cd->temp_pwd);
	new_pwd = (char **)malloc(sizeof(char *) * (ft_tablen(cd->temp_pwd)));
	if (!new_pwd)
		ft_errno(ERR_MEM, EX_MISCERROR, cd->data);
	while (i < len - 1)
	{
		temp = ft_strdup(cd->temp_pwd[i]);
		new_pwd[i] = temp;
		i++;
	}
	new_pwd[i] = NULL;
	ft_free_array(cd->temp_pwd);
	return (new_pwd);
}

/*
**	concat pwd for relative
*/
char	*ft_pwdcat(char **pwd, t_cd *cd)
{
	char	*new_pwd;
	char	*temp;
	int		i;
	int		size;

	size = ft_tablen(pwd);
	temp = NULL;
	i = 0;
	if (!pwd)
		return (NULL);
	new_pwd = ft_strdup("");
	if (!new_pwd)
		ft_errno(ERR_MEM, EX_MISCERROR, cd->data);
	while (i < size)
	{
		temp = ft_strjoin(new_pwd, "/");
		free(new_pwd);
		new_pwd = ft_strjoin(temp, pwd[i]);
		free(temp);
		i++;
	}
	pwd[i] = NULL;
	return (new_pwd);
}
