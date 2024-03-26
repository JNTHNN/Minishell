/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:29 by gdelvign         ###   ########.fr       */
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



int	ft_store_redirections(t_data *data)
{
	t_tok_lst	*current;
	t_redir_lst	**redirections;
	int			cmd_nb;
	int			i;

	current = data->tokens;
	redirections = data->redirections;
	cmd_nb = ft_count_pipes(current) + 1;
	redirections = (t_redir_lst **)malloc(cmd_nb * sizeof(t_redir_lst *));
	if (!redirections)
		return (E_MEM);
	i = -1;
	while (++i < cmd_nb)
		redirections[i] = NULL;

	i = 0;
	while (current)
	{
		while (current && current->type == WORD)
			current = current->next;
		if (!current)
			return (EXIT_SUCCESS);
		if (current->r_type == R_PIPE)
		{
			current = current->next;
			i++;
			continue ;
		}
		if (!current->next)
			return (E_REDIR);
		if (current->next->type == OPERATOR)
			return (ft_find_redir_type(current->next->token,
					current->next->type));
		if (current->type == OPERATOR)
		{
			// TODO: add node to data->redirections HERE
			ft_add_redir_node(redirections[i], current, i + 1);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_parse(t_data *data)
{
	t_tok_lst	*current;
	t_tok_lst	*start;
	char		**cmd_args;
	int			arg_count;
	int			i;

	// Store redirections and remove them from tokens list
	data->cmd = NULL;
	// TODO: store function HERE


	// Create all commands
	current = data->tokens;
	start = current;
	while (current)
	{
		arg_count = 0;
		while (current && current->token[0] != PIPE)
		{
			arg_count++;
			current = current->next;
		}
		cmd_args = (char **)malloc((arg_count + 1) * sizeof(char *));
		if (!cmd_args)
			return (E_MEM);
		i = 0;
		while (i < arg_count)
		{
			cmd_args[i] = start->token;
			start = start->next;
			i++;
		}
		cmd_args[arg_count] = NULL;
		if (ft_add_cmd_node(&cmd_args, data))
			return (E_MEM);
		if (current)
		{
			current = current->next;
			start = current;
		}
	}
	// PRINT CMD NODE ARGS
	t_cmd	*cmd;
	cmd = data->cmd;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("ARGS %i = %s\n", i, cmd->args[i]);
			i++;
		}
		cmd = cmd->right;
	}
	/* end of printing results */


	
	return (EXIT_SUCCESS);
}
