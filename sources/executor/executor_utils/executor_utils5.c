/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:20 by gdelvign          #+#    #+#             */
/*   Updated: 2024/06/03 09:24:32 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Initilizes the array of pipes
*/
void	ft_init_pipes(t_data *data, t_exec *exec)
{
	int	nb_of_pipes;
	int	i;

	nb_of_pipes = data->nb_of_cmds - 1;
	exec->pipes = (int **)malloc(nb_of_pipes * sizeof(int *));
	if (!exec->pipes)
		ft_errno(ERR_MEM, EX_MISCERROR, data);
	i = -1;
	while (++i < nb_of_pipes)
	{
		exec->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!exec->pipes[i])
			ft_errno(ERR_MEM, EX_MISCERROR, data);
		if (pipe(exec->pipes[i]) == F_ERROR)
			ft_errno(ERR_MEM, EX_MISCERROR, data);
	}
}

/*
** Closes all unnecessary pipes in the current child process.
*/
int	ft_close_pipes(t_data *data, t_exec *exec, int skip)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = data->nb_of_cmds - 1;
	while (i < nb_pipes)
	{
		if (i == skip)
			i++;
		if (i == nb_pipes)
			break ;
		if (close(exec->pipes[i][0]) == F_ERROR)
			return (E_CLOSE);
		if (i != skip - 1)
		{
			if (close(exec->pipes[i][1]) == F_ERROR)
				return (E_CLOSE);
		}
		i++;
	}
	if (close(exec->tmpin) == F_ERROR || close(exec->tmpout))
		return (E_CLOSE);
	return (EXIT_SUCCESS);
}

/*
** Closes all pipes in the parent process.
*/
int	ft_close_pipes_in_parent(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_cmds - 1)
	{
		if (close(data->exec->pipes[i][0]) == F_ERROR
			|| close(data->exec->pipes[i][1]) == F_ERROR)
			return (E_CLOSE);
	}
	return (EXIT_SUCCESS);
}

/*
** Resets standard input and output to default values at the end of execution.
*/
int	ft_reset_stdio(t_data *data)
{
	if (dup2(data->exec->tmpin, STDIN_FILENO) == F_ERROR
		|| dup2(data->exec->tmpout, STDOUT_FILENO) == F_ERROR)
		return (E_DUP);
	if (close(data->exec->tmpin) == F_ERROR
		|| close(data->exec->tmpout) == F_ERROR)
		return (E_CLOSE);
	return (EXIT_SUCCESS);
}

/*
** Splits each path from the environment variable PATH.
*/
char	**ft_path_abs(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**my_path;

	path = ft_get_env_value(data->env, "PATH");
	if (!path)
	{
		data->err_info = cmd->args[0];
		ft_handle_error(data, E_PATH);
		return (NULL);
	}
	my_path = ft_split(path, ':');
	ft_pathiter(my_path, cmd);
	return (my_path);
}
