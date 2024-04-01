/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:30:17 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/01 20:46:09 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_redir_lst	t_redir_lst;
typedef struct s_tok_lst	t_tok_lst;
typedef struct s_env		t_env;
typedef struct s_expand		t_expand;

typedef enum e_tok_type
{
	WORD,
	OPERATOR
}	t_tok_type;

typedef enum e_expand_char
{
	DBL_Q = 34,
	SGL_Q = 39,
	DOLLAR = 36
}	t_expand_char;

typedef enum e_redirect_type
{
	R_PIPE = -5,
	IN = -6,
	HEREDOC = -7,
	OUT = -8,
	OUT_T = -9
}	t_redirect_type;

struct	s_data
{
	char		*input;
	char		**env;
	char		**env_cpy;
	t_tok_lst	*tokens;
	t_redir_lst	**redirections;
	t_cmd		*cmd;
};

struct s_tok_lst
{
	int					id;
	char				*token;
	t_tok_type			type;
	t_redirect_type		r_type;
	struct s_tok_lst	*next;
	struct s_tok_lst	*prev;
};

struct s_redir_lst
{
	t_redirect_type	r_type;
	char			*filename;
	int				cmd_nb;
	t_redir_lst		*next;
	t_redir_lst		*prev;
};

struct s_env
{
	char			*var;
	struct s_env	*next;
};

struct s_cmd
{
	int					id;
	char				**args;
	t_redir_lst			*redirections;
	bool				is_builtin;
	t_data				*data;
	t_expand			**expanded_char;
	struct s_cmd		*left;
	struct s_cmd		*right;
};

struct	s_expand
{
	int				id;
	int				position;
	t_expand_char	char_type;
};

#endif