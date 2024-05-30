/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:47:38 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/30 22:03:17 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Allocate a new array of arguments to replace the old one.
*/
static int	ft_create_new_arg_array(char ***new_arr, char **old_arr)
{
	int	i;
	int	arr_len;

	i = 0;
	arr_len = 0;
	while (old_arr[i])
	{
		if (old_arr[i][0] != '\0')
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
	while (current && current->args)
	{
		if (ft_create_new_arg_array(&new_arr, current->args))
			return (E_MEM);
		i = -1;
		j = 0;
		while (++i < ft_arrlen(current->args))
			if (current->args[i][0] != '\0')
				new_arr[j++] = ft_strdup(current->args[i]);
		new_arr[j] = NULL;
		ft_free_array(current->args);
		current->args = new_arr;
		current->is_builtin = ft_is_builtin(current->args[0]);
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
