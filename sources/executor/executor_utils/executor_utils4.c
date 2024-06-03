/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/03 19:08:59 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Restores signals to default behavior to enable them in the child process.
*/
void	ft_restore_signals(bool heredoc)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	ft_signal(SIG_DFL, heredoc);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/*
** Prints "^C" and ^\Quit if needed when a process is aborted.
*/
void	ft_print_signals(int status, int flag)
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
		if (flag == EXIT_HD)
			g_exit_code = EXEC_FAIL;
	}
}

void	ft_relative_exec(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = ft_create_exec(data, cmd);
	if (ret)
		ft_handle_exec_error(cmd->args[0], ret, data);
	ft_check_type(cmd->args[0], data, EXEC_REL);
	ft_handle_error(data, E_PATH);
}

int	ft_type_of_arg(char *arg, t_data *data)
{
	if (!ft_strncmp(arg, "/", 1)
		|| !ft_strncmp(arg, "./", 2))
		return (ABS);
	else if (!ft_strncmp(arg, ".", 1)
		|| !ft_strncmp(arg, "..", 2))
	{
		if (!ft_strncmp(arg, "./", 2)
			|| !ft_strncmp(arg, "../", 3)
			|| !ft_getenv(data, "PATH="))
			return (DIR);
		return (DOT);
	}
	return (EXIT_SUCCESS);
}

int	ft_open_first_redir(t_data *data, t_cmd *cmd)
{
	t_redir_lst	*current;

	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	while (current)
	{
		if (current->r_type != HEREDOC)
			break ;
		current = current->next;
	}
	if (current)
	{
		if (current->r_type == IN)
		{
			if (ft_open_redir_in(data, cmd)
				|| ft_open_redir_out(data, cmd))
				return (E_OPEN);
		}
		else
			if (ft_open_redir_out(data, cmd)
				|| ft_open_redir_in(data, cmd))
				return (E_OPEN);
	}
	return (EXIT_SUCCESS);
}
