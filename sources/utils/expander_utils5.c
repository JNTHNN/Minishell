/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:11:08 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/30 10:13:05 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
