/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:04:06 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/08 15:52:19 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char    *ft_pwdcat(char **pwd)
{
	char	*new_pwd;
	int		i;

	i = 0;
	new_pwd = ft_strdup("");
	while (pwd[i])
	{
		new_pwd = ft_strjoin(new_pwd, "/");
		new_pwd = ft_strjoin(new_pwd, pwd[i]);
		i++;
	}
	return (new_pwd);
}