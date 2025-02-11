/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:25:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/29 15:55:43 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

enum	e_pipe_end
{
	READ_END,
	WRITE_END
};

# define FORKED_CHILD 0
# define F_ERROR -1
# define NOT_INIT -1
# define EX_MISCERROR 2
# define EXEC_FAIL 1
# define STR_QUIT "Quit: 3"
# define CLEAR_LINE "\033[2K\033[1G"
# define EXEC_REL 0
# define EXEC_ABS 1
# define EX_NOEXEC 126
# define EX_NOTFOUND 127
# define EX_BADSYNTAX 257
# define EX_USAGE	2
# define EMPTY 0
# define EXEC 1
# define ABS 1
# define DOT 2
# define DIR 3

/* executor.c */
int		ft_executor(t_data *data);

/* executor_utils.c */
void	ft_check_type(char *cmd, t_data *data, int flag);
void	ft_handle_exec_error(char *cmd, int code, t_data *data);
int		ft_create_exec(t_data *data, t_cmd *cmd);
void	ft_execute_command(t_data *data, t_cmd *cmd);
t_exec	*ft_init_exec(t_data *data);

/* executor_utils2.c */
int		ft_open_redir_in(t_data *data, t_cmd *cmd);
int		ft_open_redir_out(t_data *data, t_cmd *cmd);
int		ft_cmd_exec(t_data *data);

/* executor_utils3.c */
void	ft_free_lst(t_env *head);
int		ft_exec_cmds_loop(t_data *data, int *nb);
char	**ft_pathiter(char **path, t_cmd *cmd);

/* executor_utils4.c */
void	ft_restore_signals(bool heredoc);
void	ft_print_signals(int status, int flag);
void	ft_relative_exec(t_data *data, t_cmd *cmd);
int		ft_type_of_arg(char *arg, t_data *data);
int		ft_open_first_redir(t_data *data, t_cmd *cmd);

/* executor_utils5.c */
void	ft_init_pipes(t_data *data, t_exec *exec);
int		ft_close_pipes(t_data *data, t_exec *exec, int skip);
int		ft_close_pipes_in_parent(t_data *data);
int		ft_reset_stdio(t_data *data);
char	**ft_path_abs(t_data *data, t_cmd *cmd);

#endif