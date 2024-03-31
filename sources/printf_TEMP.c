/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_TEMP.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:02:12 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/30 22:47:35 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* print token linked list nodes to check results while coding in ft_tokenize */
	// t_tok_lst	*current;
	// current = data->tokens;
	// while (current != NULL)
	// {
	// 	printf("Token %i = %s\n", current->id, current->token);
	// 	current = current->next;
	// }
	/* end of printing results */
	


// PRINT redirections in ft_store_redirections
	// i = 0;
	// while (i < cmd_nb)
	// {
	// 	t_redir_lst *node = redirections[i];
	// 	while (node != NULL)
	// 	{
	// 		printf("node type = %i, %s\n", node->r_type, node->filename);
	// 		node = node->next;
	// 	}
	// 	i++;
	// }
// END

// PRINT CMD NODE ARGS in ft_paser
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

	#include "../includes/minishell.h"

	static const char	*redirect_type_to_string(t_redirect_type type) {
	switch (type) {
		case R_PIPE:
			return "R_PIPE";
		case IN:
			return "IN";
		case HEREDOC:
			return "HEREDOC";
		case OUT:
			return "OUT";
		case OUT_T:
			return "OUT_T";
		default:
			return "UNKNOWN";
	}
}

void	print_parse(t_cmd *cmd)
{
	int	i;
	while (cmd != NULL)
	{
		i = -1;
		printf("-------------------------\n");
		printf("COMMAND ID [%d]\n", cmd->id);
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		if (cmd->args[0] == NULL)
			printf("NO ARG\n");
		if (cmd->redirections)
		{
			if (cmd->redirections && cmd->redirections->r_type == HEREDOC)
				printf("REDIRECTION [%s] WITH DELIMITOR [%s]\n", redirect_type_to_string(cmd->redirections->r_type), cmd->redirections->filename);
			else
				printf("REDIRECTION [%s] IN [%s]\n", redirect_type_to_string(cmd->redirections->r_type), cmd->redirections->filename);
		}
		while (cmd->args[++i])
		{	
			printf("ARG [%d] = %s\n", i, cmd->args[i]);
		}
		printf("IS BUILTIN = ");
		if (cmd->is_builtin == 1)
			printf("YES\n");
		else
			printf("NO\n");
		printf("\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
		cmd = cmd->right;
		printf("-------------------------\n");
			
		
	}

}