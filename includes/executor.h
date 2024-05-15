/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:16:59 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/15 11:11:03 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

enum	e_pipe_end
{
	READ_END,
	WRITE_END
};

# define PREV(i)(i - 1)
# define FORKED_CHILD 0
# define F_ERROR -1
# define NOT_INIT -1
# define EX_MISCERROR 2
# define EXEC_FAIL 1
# define EXEC_REL 0
# define EXEC_ABS 1

void	ft_execute_command(t_data *data, t_cmd *cmd);
char	**ft_pathiter(char **path, t_cmd *cmd);
char	**ft_path_abs(t_data *data, t_cmd *cmd);
int		ft_executor(t_data *data);
int		ft_cmd_exec(t_data *data);
t_exec	*ft_init_exec(t_data *data);

#endif