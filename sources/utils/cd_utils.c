/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:27:53 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/10 15:24:37 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_seek_replace(t_data *data, char *search, char *pwd)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], search, ft_strlen(search)))
		{
			data->env[i] = ft_strjoin(search, pwd);
			found = 1;
		}
		i++;
	}
	if (!found)
		data->env = ft_add_to_env(data->env, ft_strjoin(search, pwd));
}

void	ft_cd_home(t_data *data, char *pwd)
{
	char	*new_pwd;

	new_pwd = ft_getenv(data, "HOME=");
	ft_seek_replace(data, "PWD=", new_pwd + 5);
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
}

void	ft_cd_absolute(t_data *data, char *pwd)
{
	char	*new_pwd;

	new_pwd = data->cmd->args[1];
	if (!(ft_strlen(new_pwd) == 1) && new_pwd[ft_strlen(new_pwd) - 1] == '/')
		ft_memset(new_pwd + (ft_strlen(new_pwd) - 1), 0, 1);
	ft_seek_replace(data, "PWD=", data->cmd->args[1]);
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
}

char	**ft_remove_first(char **path)
{
	char	**new_path;
	int 	i;
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

char	**ft_replace_pwd(t_data *data, char *shortcut)
{
	char	*temp_pwd;
	char	**pwd;

	printf("Shortcut [%s]\n", shortcut);
	if (shortcut && !ft_strncmp(shortcut, "-", 1))
		temp_pwd = ft_getenv(data, "OLDPWD=");
	else
		temp_pwd = ft_getenv(data, "HOME=");
	printf("REPLACE PWD [%s]\n", temp_pwd);
	pwd = ft_split(temp_pwd, '/');
	return (pwd);
}

void	ft_cd_relative(t_data *data, char *pwd)
{
	char	**temp_path;
	char	**temp_pwd;
	int		i;

	temp_path = ft_split(data->cmd->args[1], '/');
	temp_pwd = ft_split(pwd, '/');
	i = 0;
	while (temp_path[i])
	{
		printf("TEMP_PATH AVANT [%s] \n", temp_path[i++]);
	}
	if (!ft_strncmp(temp_path[0], "~", 1) || !ft_strncmp(temp_path[0], "-", 1))
	{
		temp_pwd = ft_replace_pwd(data, temp_path[0]);
		temp_path = ft_remove_first(temp_path);
	}
	i = 0;
	while (temp_path[i])
	{
		printf("TEMP_PATH APRES [%s] \n", temp_path[i++]);
	}
	i = 0;
	while (temp_pwd && temp_pwd[i])
	{
		printf("TEMP_PWD [%s] \n", temp_pwd[i++]);
	}
	i = 0;
	while (temp_path[i])
	{
		printf("TEMP PATH DANS LA BOUCLE [%s]\n", temp_path[i]);
		// if (ft_strncmp(temp_path[0], "~", 2) != 0)
		// {
		// 	printf("LA\n");
		// 	temp_pwd = ft_prepend_pwd(temp_pwd, data);
			
		// }
		if (!ft_strncmp(temp_path[i], "..", 2))
		{
			printf("ICI\n");
			temp_pwd = ft_sup_pwd(temp_pwd);
		}
		else if (ft_strncmp(temp_path[i], ".", 2) != 0)
		{
			printf("OU LA\n");
			temp_pwd = ft_append_pwd(temp_pwd, temp_path[i]);
		}
		i++;
	}
	i = 0;
	while (temp_pwd[i])
	{
		printf("TEMP_PWD FINAL [%s] \n", temp_pwd[i++]);
	}
	ft_seek_replace(data, "PWD=", ft_pwdcat(temp_pwd + 1));
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
}
