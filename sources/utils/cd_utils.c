/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:27:53 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/03 15:44:00 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	searches for variable in env, if doesn't exist -> adds it
*/
void	ft_seek_replace(t_data *data, char *search, char *pwd)
{
	int			i;
	int			found;
	static char	cwd[PATH_MAX];

	i = 0;
	found = 0;
	// if (!pwd)
	// {
	// 	printf("ici\n");
	// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
	// 		pwd = cwd;
	// 	printf("pwd = %s\n", pwd);
	// }
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		pwd = cwd;
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

/*
**	cd without args/path -> return to path in env var HOME
*/
void	ft_cd_home(t_data *data, char *pwd)
{
	char	*new_pwd;

	new_pwd = ft_getenv(data, "HOME=");
	ft_seek_replace(data, "PWD=", new_pwd + 5);
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
}

/*
**	cd with absolute path
*/
void	ft_cd_absolute(t_data *data, t_cmd *cmd, char *pwd)
{
	char	*new_pwd;

	new_pwd = cmd->args[1];
	if (!(ft_strlen(new_pwd) == 1) && new_pwd[ft_strlen(new_pwd) - 1] == '/')
		ft_memset(new_pwd + (ft_strlen(new_pwd) - 1), 0, 1);
	ft_seek_replace(data, "PWD=", cmd->args[1]);
	ft_seek_replace(data, "OLDPWD=", pwd);
}

/*
**	cd with relative path
*/
void	ft_cd_relative(t_data *data, t_cmd *cmd, char *pwd)
{
	char	**temp_path;
	char	**temp_pwd;
	int		i;

	printf("cest %s\n", pwd);
	temp_path = ft_split(cmd->args[1], '/');
	temp_pwd = ft_split(pwd, '/');
	if (!ft_strncmp(temp_path[0], "~", 1) || !ft_strncmp(temp_path[0], "-", 1))
	{
		temp_pwd = ft_replace_pwd(data, temp_path[0]);
		temp_path = ft_remove_first(temp_path);
	}
	i = 0;
	while (temp_path[i])
	{
		if (!ft_strncmp(temp_path[i], "..", 2))
			temp_pwd = ft_sup_pwd(temp_pwd);
		else if (ft_strncmp(temp_path[i], ".", 2) != 0)
			temp_pwd = ft_append_pwd(temp_pwd, temp_path[i]);
		i++;
	}
	i = 0;
	while (temp_pwd[i])
	{
		printf("temp_pwd = %s\n", temp_pwd[i]);
		i++;
	}
	ft_seek_replace(data, "PWD=", ft_pwdcat(temp_pwd));
	printf("AV OLD -> pwd = %s\n", pwd);
	ft_seek_replace(data, "OLDPWD=", pwd);
	printf("AP OLD -> pwd = %s\n", pwd);
	ft_free_array(temp_path);
	//ft_free_array(temp_pwd);
}
