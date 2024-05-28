/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/28 17:14:41 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_hd_expansion(char **line, t_data *data)
{
	int		new_length;
	char	*cursor;
	char	*str;

	str = ft_strdup(*line);
	if (!str)
		return (E_MEM);
	if (ft_count_dollars(str))
	{
		new_length = ft_calc_line_new_len(*line, data);
		free(*line);
		*line = (char *)malloc(new_length + 1);
		if (!*line)
			return (E_MEM);
		cursor = *line;
		ft_create_new_line(str, cursor, data, (new_length + 2));
	}
	free(str);
	return (EXIT_SUCCESS);
}

static int	ft_heredoc_process(t_redir_lst *node, t_data *data)
{
	char	*line;
	int		fd;

	ft_restore_signals(true);
	fd = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == F_ERROR)
		exit(E_OPEN);
	while (true)
	{
		line = readline("> ");
		if (!line)
			exit(20);
		if (!node->quoted)
			ft_handle_hd_expansion(&line, data);
		if ((line && line[0])
			&& ft_strncmp(line, node->filename, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}

static int	ft_handle_heredoc(t_redir_lst *node, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == F_ERROR)
		return (ft_errno("fork", EXEC_FAIL, data), EXIT_FAILURE);
	else if (pid == FORKED_CHILD)
		ft_heredoc_process(node, data);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			ft_print_signals(data->exec->status);
			return (EXIT_HD);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_trigger_heredoc(t_data *data)
{
	int			i;
	t_redir_lst	*current;
	int			ret;

	ret = 0;
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		current = data->redirections[i];
		while (current != NULL)
		{
			if (current->r_type == HEREDOC)
				ret = ft_handle_heredoc(current, data);
			if (ret == EXIT_HD || ret == CTRL_D)
				break ;
			if (ret == E_OPEN)
				return (E_OPEN);
			current = current->next;
		}
		if (ret)
			return (ret);
	}
	data->exec->trigger_hd = true;
	return (EXIT_SUCCESS);
}
