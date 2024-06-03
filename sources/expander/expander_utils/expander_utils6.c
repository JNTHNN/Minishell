/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:47:38 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/02 00:01:11 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if the char is valid for the environment variable name.
*/
bool	ft_is_valid_variable_char(char c)
{
	if (ft_isalnum(c) || c == UNDERSCORE)
		return (true);
	return (false);
}

/*
** Allocate a new array of arguments to replace the old one.
*/
static int	ft_create_new_arg_array(char ***new_arr, t_cmd *cmd)
{
	int	i;
	int	arr_len;

	i = 0;
	arr_len = 0;
	while (i < cmd->arg_size)
	{
		if (cmd->args[i] != NULL)
			arr_len++;
		i++;
	}
	*new_arr = (char **)malloc((arr_len + 1) * sizeof(char *));
	if (!*new_arr)
		return (E_MEM);
	return (EXIT_SUCCESS);
}

/*
** Removes empty arguments of command arguments array
** and replaces the array int the command node.
*/
int	ft_clean_expanded_args(t_data *data)
{
	t_cmd	*current;
	int		i;
	int		j;
	char	**new_arr;

	current = data->cmd;
	while (current)
	{
		if (current->args)
		{
			if (ft_create_new_arg_array(&new_arr, current))
				return (E_MEM);
			i = -1;
			j = 0;
			while (++i < current->arg_size)
				if (current->args[i] != NULL)
					new_arr[j++] = ft_strdup(current->args[i]);
			new_arr[j] = NULL;
			ft_free_array(current->args);
			current->args = new_arr;
			current->is_builtin = ft_is_builtin(current->args[0]);
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}

/*
** Handles expansion for each string in the argument array of the command.
*/
int	ft_expand_cmd_args(t_data *data)
{
	t_cmd	*current;
	int		i;
	int		ret;

	current = data->cmd;
	while (current)
	{
		i = -1;
		while (current->args && current->args[++i])
		{
			ft_should_resplit(current->args[0], data);
			ret = ft_handle_expansion(&current->args, i, data);
			if (ret)
				return (ret);
			if (!data->resplit)
			{
				ret = ft_resplit_first_arg(&current->args, current);
				if (ret)
					return (ret);
			}
		}
		current = current->right;
		data->resplit = false;
	}
	return (EXIT_SUCCESS);
}
