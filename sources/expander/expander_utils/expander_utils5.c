/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:11:08 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/31 17:10:30 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Calculates the length of a new string without quotes from the original one.
** Iterates through the original string, ignoring single and double quotes.
*/
static int	ft_count_new_delimiter_len(t_redir_lst *node)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (node->filename[i])
	{
		quote = node->filename[i];
		if (quote == DBL_Q || quote == SGL_Q)
		{
			if (node->filename[i + 1])
				i++;
			while (node->filename[i] && node->filename[i] != quote)
				ft_increment(&i, &len);
			if (node->filename[i] == quote)
				i++;
		}
		else
			ft_increment(&i, &len);
	}
	return (len);
}

/*
** Creates a new string without quotes and stores it in 'delimiter'.
** Copies characters from the original string,
** ignoring single and double quotes.
*/
static void	ft_create_new_delimiter(t_redir_lst *node, char **delimiter,
		int *i, int *j)
{
	char	quote;

	while (node->filename[*i])
	{
		quote = node->filename[*i];
		if (quote == DBL_Q || quote == SGL_Q)
		{
			(*i)++;
			while (node->filename[*i] && node->filename[*i] != quote)
			{
				(*delimiter)[*j] = node->filename[*i];
				ft_increment(i, j);
			}
			if (node->filename[*i] == quote)
				(*i)++;
		}
		else
		{
			(*delimiter)[*j] = node->filename[*i];
			ft_increment(&(*i), &(*j));
		}
	}
	(*delimiter)[*j] = '\0';
}

/*
** Handles delimiter expansion by removing quotes from the original string.
** Calculates the new length, allocates memory, and creates the new string.
*/
static int	ft_handle_delimiter_expansion(t_redir_lst *node)
{
	char	*new_delimiter;
	int		len;
	int		i;
	int		j;

	if (ft_count_all_quotes(node->filename))
		node->quoted = true;
	len = ft_count_new_delimiter_len(node);
	new_delimiter = (char *)malloc((len + 1) * sizeof(char));
	if (!new_delimiter)
		return (E_MEM);
	i = 0;
	j = 0;
	ft_create_new_delimiter(node, &new_delimiter, &i, &j);
	free(node->filename);
	node->filename = new_delimiter;
	return (EXIT_SUCCESS);
}

/*
** Creates a new expanded filename and replaces the old one.
*/
static int	ft_expand_filename(t_redir_lst *node, t_data *data)
{
	char	*new_str;
	char	*cursor;
	int		new_length;

	if (node->filename)
	{
		if (ft_count_all_quotes(node->filename)
			|| ft_count_dollars(node->filename))
		{
			if (node->r_type == HEREDOC)
				return (ft_handle_delimiter_expansion(node));
			new_length = ft_calculate_new_length(node->filename, data);
			if (new_length == 0)
				return (E_AMBIGU);
			new_str = (char *)malloc(new_length + 1);
			if (!new_str)
				return (E_MEM);
			cursor = new_str;
			ft_create_new_str(node->filename, cursor, data, (new_length + 2));
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
