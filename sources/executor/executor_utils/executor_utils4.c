/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/21 16:39:36 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_process(t_redir_lst *node)
{
	char	*line;
	int		fd;

	ft_restore_signals();
	fd = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == F_ERROR)
		exit(EXIT_FAILURE);
	while (true)
	{
		line = readline("> ");
		if (!line || ((line && line[0])
				&& ft_strncmp(line, node->filename, ft_strlen(line)) == 0))
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
	{
		if (ft_heredoc_process(node))
			return (E_OPEN);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			ft_print_signals(data->exec->status);
			return (EXIT_HD);
		}
	}
	return (EXIT_SUCCESS);
}

void	ft_restore_signals(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	ft_signal(SIG_DFL);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_print_signals(int status)
{
	if (status == SIGQUIT)
	{
		ft_putendl_fd(STR_QUIT, STDERR_FILENO);
		g_exit_code = 128 + SIGQUIT;
	}
	else
	{
		printf(CLEAR_LINE);
		g_exit_code = 128 + SIGINT;
	}
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
			{
				ret = ft_handle_heredoc(current, data);
				if (ret == EXIT_HD)
					break ;
				if (ret == E_OPEN)
					return (E_OPEN);
			}
			current = current->next;
		}
		if (ret)
			return (EXIT_HD);
	}
	data->exec->trigger_hd = true;
	return (EXIT_SUCCESS);
}
