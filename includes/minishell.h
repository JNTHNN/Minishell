/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/12 16:22:24 by gdelvign         ###   ########.fr       */
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
void	ft_test(int nb);

void	ft_show_env(char **env);
int		av_input(char *in);

/*		AV_signals								*/
void	av_signal(void);
void	av_sigint(int sig);
int		av_init_signal(void);
void	rl_replace_line(const char *text, int clear_undo);

/*		JG_builtins		*/
void	ft_builtin(char **prompt, char **my_env);
void	ft_show_env(char **env);
void	cd_builtin(char **path);
void	ft_echo_builtin(char **str);
void	exit_builtins(void);
void	pwd_builtin(void);
void	export_builtin(char **cmd, char **my_env);

/*		JG_exec			*/
int		create_exec(char **argv, char **env);
void	cmd_exec(char **cmd, char **env);


/*		UTILS		*/

char	*ft_strcat(char *dest, const char *src);
bool	ft_is_builtin(char **cmd);

#endif