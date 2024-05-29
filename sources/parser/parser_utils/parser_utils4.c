/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:25:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/24 11:27:59 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Creates the path of the temporary file for each heredoc.
*/
static int	ft_hd_path(t_redir_lst *current, int *j)
{
	char	*nb;

	nb = ft_itoa((*j)++);
	current->hd_path = ft_strjoin("/tmp/hd_temp", nb);
	free(nb);
	if (!current->hd_path)
		return (E_MEM);
	return (EXIT_SUCCESS);
}

/*
** Creates the path the temporary file for each heredoc.
*/
int	ft_build_hd_path(t_data *data)
{
	int			i;
	int			j;
	t_redir_lst	*current;

	i = -1;
	j = 1;
	while (++i < data->nb_of_cmds)
	{
		if (data->redirections[i])
		{
			current = data->redirections[i];
			while (current != NULL)
			{
				if (current->r_type == HEREDOC)
				{
					if (ft_hd_path(current, &j))
						return (E_MEM);
				}
				current = current->next;
			}
		}
	}
	return (EXIT_SUCCESS);
}

/*
** Adds an id at each redir node.
*/
void	ft_add_redir_node_id(t_redir_lst **redirections)
{
	int			i;
	t_redir_lst	*current;

	current = *redirections;
	if (current)
	{
		i = 0;
		while (current != NULL)
		{
			current->id = ++i;
			current = current->next;
		}
	}
}
