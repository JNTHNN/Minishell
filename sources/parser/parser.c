/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/21 23:43:13 by gdelvign         ###   ########.fr       */
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
	char		**cmd_args;

	data->cmd = NULL;
	current = data->tokens;
	while (current->next != NULL
		&& current->type != OPERATOR && current->token[0] != PIPE)
		current = current->next;
	cmd_args = (char **)malloc(current->id * sizeof(char *));
	if (!cmd_args)
		ft_throw_error(data, 0, ERR_MEM);
	i = current->id;
	i--;
	cmd_args[i] = NULL;
	i--;
	while (i >= 0)
	{
		cmd_args[i] = current->prev->token;
		if (current->prev != NULL)
			current = current->prev;
		i--;
	}
	
	// Print test
	i = 0;
	while (cmd_args[i] != NULL)
	{
		printf("ARGS %i = %s\n", i, cmd_args[i]);
		i++;
	}
	
	
	// create new cmd node 
	


		
		// agregate all previous nodes in one t_cmd node
	
	return (EXIT_SUCCESS);
}
