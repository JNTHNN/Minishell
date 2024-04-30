/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:25:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/29 15:55:43 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
					current->hd_path = ft_strjoin("/tmp/hd_temp", ft_itoa(j++));
					if (!current->hd_path)
						return (E_MEM);
				}
				current = current->next;
			}
		}
	}
	return (EXIT_SUCCESS);
}

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
