/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/22 17:17:56 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_pipes(t_tok_lst *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (lst->type == OPERATOR && lst->token[0] == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_parse(t_data *data)
{
	t_tok_lst	*current;
	t_tok_lst	*last_position;
	int			i;
	char		**cmd_args;

	data->cmd = NULL;
	current = data->tokens;
	if (ft_count_pipes(current) == 0)
	{
		current = ft_tok_lstlast(current);
		cmd_args = (char **)malloc((current->id + 1) * sizeof(char *));
		if (!cmd_args)
			return (E_MEM);
		i = current->id;
		cmd_args[i] = NULL;
		i--;
		while (i >= 0)
		{
			cmd_args[i] = current->token;
			if (current->prev != NULL)
				current = current->prev;
			i--;
		}
		ft_add_cmd_node(cmd_args, data);
	}
	else
	{
		int j = 0;
		while (current->next != NULL)
		{
			last_position = current;
			if (current->token[0] == PIPE)
			{
				j = current->id - j;
				cmd_args = (char **)malloc(j * sizeof(char *));
				if (!cmd_args)
					return (E_MEM);
				i = j - 1;
				cmd_args[i] = NULL;
				i--;
				while (i >= 0 && current->token[0] != PIPE)
				{
					cmd_args[i] = current->prev->token;
					if (current->prev != NULL)
						current = current->prev;
					i--;
				}
				ft_add_cmd_node(cmd_args, data);
			}
			current = last_position->next;
		}
	}
	
	
	// Print ARGS
	// i = 0;
	// while (cmd_args[i] != NULL)
	// {
	// 	printf("ARGS %i = %s\n", i, cmd_args[i]);
	// 	i++;
	// }

	// PRINT CMD NODE ARGS
		/* print token linked list nodes to check results while coding */
	t_cmd	*cmd;
	cmd = data->cmd;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->args[i])
	{
		printf("TEST -\n");
		printf("ARGS %i = %s\n", i, cmd->args[i]);
		i++;
	}
		cmd = cmd->right;
	}
	/* end of printing results */

	
	return (EXIT_SUCCESS);
}
