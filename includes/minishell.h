/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/02/01 17:07:18 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <stdbool.h> // type bool
# include <sys/syslimits.h> // PATH_MAX

typedef	struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;


/*		TEMP		*/

void	show_env(char **env);
void	builtin_env(char **env);
void	builtin_hist(HIST_ENTRY **history);
int		av_input(char *in);

/*		AV_signals								*/
void	av_signal(void);
void	av_sigint(int sig);
int		av_init_signal(void);

/*		JG_builtins		*/
void	ft_builtin(char **prompt, char **my_env);
void	show_env(char **env);
void	cd_builtin(char **path);
void	echo_builtin(char **str);
void	exit_builtins(void);
void	pwd_builtin(void);
void	export_builtin(char **cmd, char **my_env);

/*		JG_exec			*/
int		create_exec(char **argv, char **env);
void	cmd_exec(char **cmd, char **env);

void	rl_replace_line(const char *text, int clear_undo);

/*		UTILS		*/

char	*ft_strcat(char *dest, const char *src);
bool	is_builtin(char **cmd);

#endif