/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:43:30 by anvoets           #+#    #+#             */
/*   Updated: 2024/04/15 21:48:00 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_get_ctrl_d(t_data *data)
{
	if (data->input == NULL)
	{
		printf("\033[A\033[2K");
		printf("%s", PROMPT "exit\n");
		exit(0);
	}
}

/* personnalize interruptions */
int	ft_init_signal(void)
{
	struct termios	term;

	ft_signal();
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
