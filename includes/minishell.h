/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:19 by anvoets           #+#    #+#             */
/*   Updated: 2024/03/16 22:49:55 by gdelvign         ###   ########.fr       */
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
# include "error.h"
# include "lexer.h"
# include "utils.h"

# define PROMPT "\033[0;33mminibash1.0$ \033[0m"

typedef enum e_token_type
{
	LITTERAL,
	CMD,
	ARGUMENT,
	REDIRECT_OPERATOR,
	PIPE,
	ENV_VAR,
	EXIT_CODE,
	BUILTIN
}	t_token_type;

typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_BUILTIN,
	CMD_PIPE,
	CMD_REDIRECT
}	t_cmd_type;

typedef struct s_data
{
	char	*input;
	char	**env;
	char	**env_cpy;
}	t_data;

typedef struct s_token_lst
{
	int					id;
	char				*token;
	t_token_type		type;
	struct t_token_lst	*next;
	struct t_token_lst	*prev;
}	t_token_lst;

typedef struct s_ast_node
{
	t_cmd_type			type;
	char				**args;
	struct t_ast_node	*left;
	struct t_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

void		ft_show_env(char **env);
int			ft_input(char *in);

/* Handle tokenization : t_tokenizer.c */
t_token_lst	*ft_tokenize(char *input);

/* Handle signals : s_signals.c	*/
void		ft_signal(void);
void		ft_sigint(int sig);
int			ft_init_signal(void);
void		rl_replace_line(const char *text, int clear_undo);

/* Handle all builtins : builtins.c	*/
bool		ft_is_builtin(char **cmd);
void		ft_builtin(char **prompt, char **my_env);

void		ft_show_env(char **env);
void		cd_builtin(char **path);
void		ft_echo_builtin(char **str);
void		exit_builtins(void);
void		pwd_builtin(void);
void		export_builtin(char **cmd, char **my_env);

/*		JG_exec			*/
int			create_exec(char **argv, char **env);
void		cmd_exec(char **cmd, char **env);

/*		UTILS		*/

char		*ft_strcat(char *dest, const char *src);

#endif