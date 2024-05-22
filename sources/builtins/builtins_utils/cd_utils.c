/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:27:53 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/17 18:16:01 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	searches for variable in env, if doesn't exist -> adds it
*/
void	ft_seek_replace(t_data *data, char *search, char *pwd)
{
	int			i;
	int			found;

	i = 0;
	found = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], search, ft_strlen(search)))
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin(search, pwd);
			found = 1;
		}
		i++;
	}
	if (!found)
	{
		if (!ft_strncmp(search, OLDPWD, ft_strlen(search)) && !pwd)
			pwd = ft_strdup("");
		data->env = ft_add_to_env(data->env, ft_strjoin(search, pwd));
	}
}

/*
**	cd without args/path -> change data for PWD / OLDPWD in env
*/
void	ft_cd_home(t_cd *cd)
{
	ft_seek_replace(cd->data, PWD, cd->home + 5);
	ft_seek_replace(cd->data, OLDPWD, cd->pwd);
}

/*
**	cd with absolute path
*/
void	ft_cd_absolute(t_cd *cd)
{
	char	*new_pwd;

	new_pwd = cd->dir;
	if (!(ft_strlen(new_pwd) == 1) && new_pwd[ft_strlen(new_pwd) - 1] == '/')
		ft_memset(new_pwd + (ft_strlen(new_pwd) - 1), 0, 1);
	ft_seek_replace(cd->data, PWD, new_pwd);
	ft_seek_replace(cd->data, OLDPWD, cd->pwd);
}

/*
**	cd with relative path
*/
void	ft_cd_relative(t_cd *cd)
{
	int		i;
	char	*new_pwd;

	cd->temp_path = ft_split(cd->dir, '/');
	cd->temp_pwd = ft_split(cd->pwd, '/');
	if (!ft_strncmp(cd->temp_path[0], TILDE, 1)
		|| !ft_strncmp(cd->temp_path[0], MINUS, 1))
	{
		cd->temp_pwd = ft_replace_pwd(cd, cd->temp_path[0]);
		cd->temp_path = ft_remove_first(cd->temp_path, cd);
	}
	i = 0;
	while (cd->temp_path[i])
	{
		if (!ft_strncmp(cd->temp_path[i], PARENT, 2))
			cd->temp_pwd = ft_sup_pwd(cd->temp_pwd, cd);
		else if (ft_strncmp(cd->temp_path[i], CURRENT, 2) != 0)
			cd->temp_pwd = ft_append_pwd(cd->temp_pwd, cd->temp_path[i], cd);
		i++;
	}
	new_pwd = ft_pwdcat(cd->temp_pwd, cd);
	ft_seek_replace(cd->data, PWD, new_pwd);
	ft_seek_replace(cd->data, OLDPWD, cd->pwd);
}
