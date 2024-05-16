/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:05:22 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_heredoc(t_redir_lst *node)
{
	char	*line;
	int		fd;

	fd = open(node->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == F_ERROR)
		return (EXIT_FAILURE);
	while (true)
	{
		line = readline("> ");
		if (ft_strncmp(line, node->filename, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_cmd_exec(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == F_ERROR)
		return (ft_errno("fork", EXEC_FAIL, data), EXIT_FAILURE);
	else if (pid == FORKED_CHILD)
	{
		ft_restore_signals();
		ft_execute_command(data, data->cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			ft_print_signals(status);
	}
	return (EXIT_SUCCESS);
}

void	ft_restore_signals(void)
{
	struct termios	term;

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
		g_exit_code = 131;
	}
	else
	{
		printf(CLEAR_LINE);
		g_exit_code = 130;
	}
}

int	ft_trigger_heredoc(t_data *data)
{
	int			i;
	t_redir_lst	*current;

	i = -1;
	while (++i < data->nb_of_cmds)
	{
		if (data->redirections[i])
		{
			current = data->redirections[i];
			while (current != NULL)
			{
				if (current->r_type == HEREDOC)
				{
					if (ft_handle_heredoc(current))
						return (EXIT_FAILURE);
				}
				current = current->next;
			}
		}
	}
	data->exec->trigger_hd = true;
	return (EXIT_SUCCESS);
}
