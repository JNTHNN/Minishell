/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AV_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:43:30 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/04 14:57:41 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	av_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	av_signal(void)
{
	signal(SIGINT, av_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	av_input(char *in)
{
	if (ft_strlen(in) > 0)
		printf("%s\n", in);
	return (EXIT_SUCCESS);
}

/* replace ctrl+D,\,C (/D,/C,/\) with empty space to not parse signal commands (i think) */
int	av_init_signal(void)
{
	struct termios	term;

	av_signal();
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
