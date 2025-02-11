/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:19:45 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/03 12:04:00 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	static char	cwd[PATH_MAX];
	char		*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else if (ft_getenv(data, PWD))
	{
		pwd = ft_getenv(data, PWD);
		printf("%s\n", pwd + 4);
	}
	else
		ft_errno("pwd", EXEC_FAIL, data);
}
