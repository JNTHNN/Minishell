/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:11:08 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/30 21:32:25 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Creates a new expanded filename and replaces the old one.
*/
static int	ft_expand_filename(t_redir_lst *node, t_data *data)
{
	char	*str;
	char	*new_str;
	char	*cursor;
	int		new_length;

	if (node->filename)
	{
		str = node->filename;
		if (ft_count_all_quotes(str) || ft_count_dollars(str))
		{
			if (ft_is_quote(str[0]))
				node->quoted = true;
			new_length = ft_calculate_new_length(str, data);
			new_str = (char *)malloc(new_length + 1);
			if (!new_str)
				return (E_MEM);
			cursor = new_str;
			ft_create_new_str(str, cursor, data, (new_length + 2));
			free(node->filename);
			node->filename = new_str;
		}
	}
	return (EXIT_SUCCESS);
}

/*
** Handles expansion for all redirection (filename).
*/
int	ft_expand_redir(t_data *data)
{
	int			i;
	int			ret;
	t_redir_lst	*current;

	i = -1;
	while (++i < data->nb_of_cmds)
	{
		if (data->redirections[i])
		{
			current = data->redirections[i];
			while (current != NULL)
			{
				ret = ft_expand_filename(current, data);
				if (ret)
					return (ret);
				current = current->next;
			}
		}
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
				ret = ft_resplit_first_arg(&current->args);
				if (ret)
					return (ret);
			}
		}
		current = current->right;
		data->resplit = false;
	}
	return (EXIT_SUCCESS);
}

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
** Removes empty arguments of command arguments array
** execpt if there is more than one and replaces the array.
*/
int	ft_clean_expanded_args(t_data *data)
{
	t_cmd	*current;
	int		i;
	int		j;
	int		arr_len;
	char	**new_arr;

	current = data->cmd;
	while (current && current->args)
	{
		i = 0;
		arr_len = 0;
		while (current->args[i])
		{
			if (current->args[i][0] != '\0')
				arr_len++;
			i++;
		}
		new_arr = (char **)malloc((arr_len + 1) * sizeof(char *));
		if (!new_arr)
			return (E_MEM);
		i = -1;
		j = 0;
		while (++i < ft_arrlen(current->args))
		{
			if (current->args[i][0] != '\0')
			{
				new_arr[j] = ft_strdup(current->args[i]);
				j++;
			}
		}
		new_arr[j] = NULL;
		ft_free_array(current->args);
		current->args = new_arr;
		current->is_builtin = ft_is_builtin(current->args[0]);
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
