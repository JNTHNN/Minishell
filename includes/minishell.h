/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/30 11:34:57 by jgasparo         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "typedef.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "clean.h"

# define PROMPT "\033[0;33mminibash1.0$ \033[0m"

void	ft_show_env(char **env);
int		ft_input(char *in);

/* Handle tokenization : t_tokenizer.c */
int		ft_tokenize(t_data *data);

/* Handle signals : s_signals.c	*/
void	ft_signal(void);
void	ft_sigint(int sig);
int		ft_init_signal(void);
void	rl_replace_line(const char *text, int clear_undo);

/* Handle all builtins : builtins.c	*/
bool	ft_is_builtin(char *name);
void	ft_builtin(char **prompt, char **my_env);

void	ft_env(char **env);
void	ft_cd(char **path);
void	ft_echo(char **str);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_export(char **cmd, char **my_env);

/*		JG_exec			*/
int		ft_create_exec(char **argv, char **env);
void	ft_cmd_exec(char **cmd, char **env);

/*		UTILS		*/

char	*ft_strcat(char *dest, const char *src);

/* Handle errors : error.c */
void	ft_throw_error(t_data *data, int err_code);

/* Lexer utils to handle t_tok_lst : lexer_utils.c */
int		ft_add_tok_node(char *str, int id, t_tok_type type, t_data *data);

/*	temp	*/
void	print_parse(t_cmd *cmd); // printf_TEMP.c



#endif