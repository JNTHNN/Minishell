/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/20 22:36:45 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parse(t_data *data)
{
	t_tok_lst	*current;

	current = data->tokens;
	while (current != NULL)
	{
		// agregate all previous nodes in one t_cmd node
		if (current->token == PIPE)
			break ;
		{
			
			
		}
	}
}
