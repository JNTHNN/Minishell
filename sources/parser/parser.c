/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/30 11:32:15 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove_redir(t_tok_lst *lst)
{
	t_tok_lst	*current;
	t_tok_lst	*tmp;

	current = lst;
	while (current)
	{
		tmp = current->next;
		if (current->type == OPERATOR && current->r_type != R_PIPE)
		{
			tmp = current->next->next;
			ft_nullify_tok_nodes(current);
		}
		current = tmp;
	}
}

int	ft_init_redir(t_redir_lst ***redirections, t_data **data, int *cmd_nb)
{
	int	i;

	*cmd_nb = ft_count_pipes((*data)->tokens) + 1;
	*redirections = (t_redir_lst **)malloc(*cmd_nb * sizeof(t_redir_lst *));
	if (!*redirections)
		return (E_MEM);
	(*data)->redirections = *redirections;
	i = -1;
	while (++i < *cmd_nb)
		(*redirections)[i] = NULL;
	return (EXIT_SUCCESS);
}

int	ft_redir_loop(t_tok_lst **current, t_redir_lst ***redirections, int *i)
{
	while (*current)
	{
		while (*current && (*current)->type == WORD)
			*current = (*current)->next;
		if (!*current)
			break ;
		if ((*current)->r_type == R_PIPE)
		{
			*current = (*current)->next;
			(*i)++;
			continue ;
		}
		if (!(*current)->next)
			return (E_REDIR);
		if ((*current)->next->type == OPERATOR)
			return (ft_find_redir_type((*current)->next->token,
					(*current)->next->type));
		if ((*current)->type == OPERATOR)
			if (ft_add_redir_node(&(*redirections)[*i], *current, *i + 1))
				return (E_MEM);
		if (*current)
			*current = (*current)->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_store_redirections(t_data *data)
{
	t_tok_lst	*current;
	t_redir_lst	**redirections;
	int			cmd_nb;
	int			ret;
	int			i;
	int			ret;
	int			i;

	cmd_nb = 0;
	i = 0;
	current = data->tokens;
	if (ft_init_redir(&redirections, &data, &cmd_nb))
	if (ft_init_redir(&redirections, &data, &cmd_nb))
		return (E_MEM);
	ret = ft_redir_loop(&current, &redirections, &i);
	if (ret)
		return (ret);
	ft_remove_redir(data->tokens);
	return (EXIT_SUCCESS);
}

void	ft_fill_cmd_args(int count, char ***args, t_tok_lst **start)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		while (!(*start)->token)
			*start = (*start)->next;
		(*args)[i] = (*start)->token;
		*start = (*start)->next;
	}
	(*args)[count] = NULL;
}

int ft_parse_loop(t_tok_lst **current, char ***args, t_data *data)
{
	t_tok_lst	*start;
	int			arg_count;
	int			cmd_id;

	cmd_id = 0;
	while (*current)
	{
		start = *current;
		arg_count = 0;
		while (*current && (*current)->r_type != R_PIPE)
		{
			if ((*current)->token)
				arg_count++;
			*current = (*current)->next;
		}
		*args = (char **)malloc((arg_count + 1) * sizeof(char *));
		if (!*args)
			return (E_MEM);
		ft_fill_cmd_args(arg_count, &(*args), &start);
		cmd_id++;
		if (ft_add_cmd_node(&(*args), data, cmd_id))
			return (E_MEM);
		if (*current)
			*current = (*current)->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_parse(t_data *data)
{
	t_tok_lst	*current;
	char		**cmd_args;
	int			ret;

	current = data->tokens;
	ret = ft_store_redirections(data);
	if (ret)
		return (ret);
	ret = ft_parse_loop(&current, &cmd_args, data);
	if (ret)
		return (ret);

	// PRINT CMD NODE ARGS
	t_cmd	*cmd;
	cmd = data->cmd;
	while (cmd != NULL)
	{
		printf("CMD ID = %i\n", cmd->id);
		if (cmd->redirections)
			printf("Belongs to %i\n", cmd->redirections->cmd_nb);
		int i;
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
	
	return (EXIT_SUCCESS);
}
