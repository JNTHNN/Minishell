/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/21 16:47:50 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_count_args(t_tok_lst *tok_lst)
// {
// 	int	i;

// 	i = 0;
// 	while (tok_lst->type != OPERATOR && tok_lst->token[0] != PIPE)
// 		i++;
// 	return (i);
// }

int	ft_parse(t_data *data)
{
	t_tok_lst	*current;
	int			i;

	current = data->tokens;
	i = 0;
	while (current != NULL)
	{
		if (current->type != OPERATOR && current->token[0] != PIPE)
			i++;
		else
			i = 0;
		printf("nb of nodes = %i\n", i);
		current = current->next;
		// agregate all previous nodes in one t_cmd node
	}
	return (EXIT_SUCCESS);
}
