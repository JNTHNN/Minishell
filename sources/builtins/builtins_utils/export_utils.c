/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:26:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/28 18:35:33 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Checker for var name | return false if error
*/
static bool	ft_check_name_var(t_env *current, char *name)
{
	if ((ft_strncmp(current->var, name, ft_strlen(current->var)) == -61
			|| ft_strncmp(current->var, name, ft_strlen(current->var)) == 61)
		|| ((!ft_strncmp(current->var, name, ft_strlen(current->var))
				&& !ft_strncmp(current->var, name, ft_strlen(current->var)))))
		return (true);
	return (false);
}

/*
**	scans the env table to modify the variable: name / data
*/
static int	ft_modify(t_env *current, char *name, char *data)
{
	int	ret;

	ret = 0;
	while (current)
	{
		if (ft_check_name_var(current, name))
		{
			if (data)
			{
				if (!current->data)
				{
					free(current->var);
					current->var = ft_strdup(name);
				}
				ft_reset_env_var(name, current->data);
				current->data = ft_strdup(data);
				free(data);
				return (MODIFY);
			}
			return (EXIST);
		}
		current = current->next;
	}
	return (ADD);
}

/*
**	Check if var env (with or w/o data) already exist then modify
**	or just add (name or name + data)
*/
void	ft_modify_or_add_env(t_env **head, char *var, t_data *system)
{
	t_env	*current;
	char	*name;
	char	*data;
	int		ret;

	name = ft_var(var);
	data = ft_data(var);
	current = *head;
	ret = ft_modify(current, name, data);
	if (!ret)
	{
		ret = ft_add_env(head, name, data);
		if (ret)
			ft_errno(ERR_MEM, EX_MISCERROR, system);
	}
	if (ret != MODIFY)
		ft_reset_env_var(name, data);
}
