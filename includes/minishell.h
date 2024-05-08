/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/05/08 16:52:59 by jgasparo         ###   ########.fr       */
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

# define PROMPT "\033[0;33mminibash1.0$ \033[0m"

extern int	g_exit_code;

void	ft_show_env(char **env);
int		ft_input(char *in);

/* Handle tokenization : t_tokenizer.c */
int		ft_tokenize(t_data *data);

/* Handle signals : s_signals.c	*/
void	ft_signal(void *type);
void	ft_sigint(int sig);
int		ft_init_signal(void);
void	rl_replace_line(const char *text, int clear_undo);
void	ft_get_ctrl_d(t_data *data);

/* Handle errors : error.c */
int		ft_handle_error(t_data *data, int ret);
void	ft_handle_arg_error(int argc, char **argv);

/* Lexer utils to handle t_tok_lst : lexer_utils.c */
int		ft_add_tok_node(char *str, int id, t_tok_type type, t_data *data);

/*  lexer.c */
int		ft_check_quotes(char *input);

#endif