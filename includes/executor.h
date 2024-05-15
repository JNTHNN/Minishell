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

# define EXEC_REL 0
# define EXEC_ABS 1
# define FORKED_CHILD 0
# define F_ERROR -1
# define NOT_INIT -1
# define EX_MISCERROR 2
# define EXEC_FAIL 1
# define STR_QUIT "Quit: 3"
# define CLEAR_LINE "\033[2K\033[1G"

/* exec_utils.c */
void	execute_command(t_data *data, t_cmd *cmd);
char	**ft_pathiter(char **path, t_cmd *cmd);
char	**ft_path_abs(t_data *data, t_cmd *cmd);
int		ft_create_exec(t_data *data, t_cmd *cmd);
t_exec	*ft_init_exec(t_data *data);

/* exec_utils2.c */
int		ft_open_redir_in(t_data *data, t_cmd *cmd);
int		ft_open_redir_out(t_data *data, t_cmd *cmd);

/* executor.c */
int		ft_cmd_exec(t_data *data);
int		ft_executor(t_data *data);

#endif