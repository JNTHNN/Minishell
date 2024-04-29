/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:42:39 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/29 15:56:04 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	cmd_nb = 0;
	i = 0;
	current = data->tokens;
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

int	ft_parse_loop(t_tok_lst **current, char ***args, t_data *data)
{
	t_tok_lst	*start;
	int			arg_count;
	int			cmd_id;

	cmd_id = 0;
	while (*current)
	{
		start = *current;
		arg_count = ft_count_cmd_args(current);
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
	data->nb_of_cmds = cmd_id;
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
	ret = ft_build_hd_path(data);
	if (ret)
		return (ret);
	return (EXIT_SUCCESS);
}
