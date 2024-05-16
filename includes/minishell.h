/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/05/16 12:19:55 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/syslimits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "typedef.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "utils.h"
# include "clean.h"
# include "history.h"
# include "executor.h"
# include "builtins.h"
# include "signals.h"

# define PROMPT "\033[0;33mminibash1.0$ \033[0m"

extern int	g_exit_code;

void	ft_show_env(char **env);
int		ft_input(char *in);

#endif