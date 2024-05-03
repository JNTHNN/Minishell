/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:25:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/29 15:55:43 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define FORKED_CHILD 0
# define F_ERROR -1
# define NOT_INIT -1

enum	e_pipe_end
{
	READ_END,
	WRITE_END
};

void	execute_command(t_data *data, t_cmd *cmd);
char	**ft_pathiter(char **path, t_cmd *cmd);
char	**ft_path_abs(t_data *data, t_cmd *cmd);
int		ft_create_exec(t_data *data, t_cmd *cmd);
int		ft_executor(t_data *data);
int		ft_cmd_exec(t_data *data);
t_exec	*ft_init_exec(t_data *data);

#endif