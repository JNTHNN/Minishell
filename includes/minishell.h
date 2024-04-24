/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/04/23 22:25:43 by gdelvign         ###   ########.fr       */
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

# define PROMPT "\033[0;33mminibash1.0$ \033[0m"

extern int	exit_code;

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

/* Handle all builtins : builtins.c	*/
bool	ft_is_builtin(char *name);
int		ft_builtin(t_data *data, t_cmd *cmd);

void	ft_echo(t_data *data, t_cmd *cmd);
void	ft_cd(t_data *data, t_cmd *cmd);
void	ft_pwd(t_data *data);
void	ft_export(t_data *data, t_cmd *cmd);
void	ft_env(t_data *data);
void	ft_exit(t_data *data);
void	ft_unset(t_data *data, t_cmd *cmd);

/*  utils for export : export_utils.c   */
t_env	*ft_setup_env(char **env);
void	ft_modify_or_add_env(t_env **head, char *var);

/* prints for export : export_utils2.c  */
void	ft_print_env(t_env *head);

/* update_env for export : export_utils3.c    */
void	ft_update_env(t_env *head, t_data *data);

/*  var + data for export : export_utils4.c */
char	*ft_var(char *s);
char	*ft_data(char *s);

/*  utils for cd : cd_utils.c   */
void	ft_seek_replace(t_data *data, char *search, char *pwd);
void	ft_cd_home(t_data *data, char *pwd);
void	ft_cd_absolute(t_data *data, t_cmd *cmd, char *pwd);
void	ft_cd_relative(t_data *data, t_cmd *cmd, char *pwd);

/*  manipulate tab for cd : cd_utils2.c */
char	**ft_append_pwd(char **pwd, char *path);
char	**ft_sup_pwd(char **pwd);
char	*ft_pwdcat(char **pwd);
char	**ft_remove_first(char **path);
char	**ft_replace_pwd(t_data *data, char *shortcut);

/*	checker for cd : cd_utils3.c	*/
int		ft_check_tilde(t_data *data);
int		ft_check_home(t_data *data);
int		ft_check_minus(t_data *data);

/*		UTILS		*/
char	*ft_strcat(char *dest, const char *src);

/* Handle errors : error.c */
int		ft_handle_error(t_data *data, int ret);
void	ft_handle_arg_error(int argc, char **argv);

/* Lexer utils to handle t_tok_lst : lexer_utils.c */
int		ft_add_tok_node(char *str, int id, t_tok_type type, t_data *data);

/*	temp	*/
void	print_parse(t_cmd *cmd); // printf_TEMP.c

/*  lexer.c */
int		ft_check_quotes(char *input);

#endif