/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_TEMP.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:02:12 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/27 22:07:24 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PRINT redirections 
	i = 0;
	while (i < cmd_nb)
	{
		t_redir_lst *node = redirections[i];
		while (node != NULL)
		{
			printf("node type = %i, %s\n", node->r_type, node->filename);
			node = node->next;
		}
		i++;
	}
// END

// PRINT CMD NODE ARGS
	t_cmd	*cmd;
	cmd = data->cmd;
	while (cmd != NULL)
	{
		printf("CMD ID = %i\n", cmd->id);
		if (cmd->redirections)
			printf("Belongs to %i\n", cmd->redirections->cmd_nb);
		i = 0;
		while (cmd->args[i])
		{
			printf("ARGS %i = %s\n", i, cmd->args[i]);
			i++;
		}
		printf("IS_BUILTIN = %i\n", cmd->is_builtin);
		cmd = cmd->right;
	}
	/* end of printing results */	