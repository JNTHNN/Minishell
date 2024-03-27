/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_TEMP.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:02:12 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/27 15:45:19 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

	/* print token linked list nodes to check results while coding */
	// t_tok_lst	*current;
	// current = data->tokens;
	// while (current != NULL)
	// {
	// 	printf("Token %i = %s\n", current->id, current->token);
	// 	current = current->next;
	// }
	/* end of printing results */

	/* DANS FT_TOKENIZE	*/

void	print_token(t_tok_lst *data)
{

}

	// PRINT CMD NODE ARGS
	// t_cmd	*cmd;
	// cmd = data->cmd;
	// while (cmd != NULL)
	// {
	// 	printf("CMD ID = %i\n", cmd->id);
	// 	if (cmd->redirections)
	// 		printf("Belongs to %i\n", cmd->redirections->cmd_nb);
	// 	i = 0;
	// 	while (cmd->args[i])
	// 	{
	// 		printf("ARGS %i = %s\n", i, cmd->args[i]);
	// 		i++;
	// 	}
	// 	printf("IS_BUILTIN = %i\n", cmd->is_builtin);
	// 	cmd = cmd->right;
	// }
	/* end of printing results */
	/*	DANS FT_PARSE	*/

void	print_parse(t_cmd *cmd)
{
	int	i;
	while (cmd != NULL)
	{
		printf("-------------------------\n");
		printf("COMMAND ID [%d]\n", cmd->id);
		printf("/\\/\\/\\/\\/\\\n");
		i = -1;
		while (cmd->args[++i])
		
			printf("ARG [%d] = %s\n", i, cmd->args[i]);
		printf("IS BUILTIN = ");
		if (cmd->is_builtin == 1)
			printf("YES\n");
		else
			printf("NO\n");
		cmd = cmd->right;
			
		
	}

}