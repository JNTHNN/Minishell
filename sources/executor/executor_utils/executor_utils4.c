/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/28 17:01:19 by gdelvign         ###   ########.fr       */
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
