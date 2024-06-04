/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/04 20:20:26 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If heredoc delimiter isn't surrounded by quotes, this function handles
** environment variables expansion in the heredoc. 
*/
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

/*
** Opens the heredoc temp file and write the readline line inside for each input.
*/
static int	ft_heredoc_process(t_redir_lst *node, t_data *data)
{
	char	*line;
	int		fd;
	size_t	len;

	fd = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == F_ERROR)
		exit(E_OPEN);
	while (true)
	{
		line = readline("> ");
		if (!line)
			exit(CTRL_D);
		len = ft_strlen(line);
		if (ft_count_dollars(line) && !ft_strncmp(line, node->filename, len))
			break ;
		else if (!node->quoted)
			ft_handle_hd_expansion(&line, data);
		if ((line && line[0]) && !ft_strncmp(line, node->filename, len))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}

/*
** Creates a child process to handle each heredoc.
*/
static int	ft_handle_heredoc(t_redir_lst *node, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == F_ERROR)
		return (ft_errno("fork", EXEC_FAIL, data), EXIT_FAILURE);
	else if (pid == FORKED_CHILD)
	{
		ft_restore_signals(true);
		ft_heredoc_process(node, data);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			ft_print_signals(data->exec->status, EXIT_HD);
			return (EXIT_HD);
		}
	}
	return (EXIT_SUCCESS);
}

/*
** Triggers the heredoc logic to handle all heredoc in the input.
*/
int	ft_trigger_heredoc(t_data *data)
{
	int			i;
	t_redir_lst	*current;
	int			ret;

	ret = 0;
	i = -1;
	g_exit_code = 0;
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

/*
** Checks if the ft_trigger_heredoc has already been triggered or not.
** Useful when there are more than one command; heredoc logic should only be
** triggered once.
*/
int	ft_check_heredoc(t_data *data)
{
	int	ret;

	ret = 0;
	if (data->exec->trigger_hd == false)
	{
		ret = ft_trigger_heredoc(data);
		if (ret)
			return (ret);
	}
	return (EXIT_SUCCESS);
}
