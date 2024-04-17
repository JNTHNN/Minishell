/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/30 19:53:04 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_exec(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			printf("^\\Quit: %d\n", SIGQUIT);
	}
	else
	{
		ft_signal(SIG_DFL);
		execute_command(data);
	}
	return (EXIT_SUCCESS);
}

t_redir_lst *ft_find_last_redir(t_redir_lst **lst, t_redirect_type type)
{
	t_redir_lst *is_last;

	is_last = NULL;
	if (!*lst)
		return (NULL);
	while (*lst)
	{
		if ((*lst)->r_type == type)
			is_last = (*lst);
		*lst = (*lst)->next;
	}
	// printf("IS_LAST = %s / R_TYPE = %d\n", is_last->filename, is_last->r_type);
	return (is_last);
}

int	ft_executor(t_data *data)
{
	t_exec	*exec;
	int		i;


	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->pipe_fd = (int **)malloc(sizeof(int *) * data->nb_of_cmds);

	if (data->nb_of_cmds == 1)
	{
		exec->pipe_fd[0] = (int *)malloc(sizeof(int) * 2);
		if (ft_find_last_redir(&data->cmd->redirections, HEREDOC))
			pipe(exec->pipe_fd[0]);
		if (!data->cmd->is_builtin)
			return (ft_cmd_exec(data));
		else
			return (ft_builtin(data));
	}

	i = -1;
	while (++i < data->nb_of_cmds)
		exec->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		printf("I [%d]\n", i);
		pipe(exec->pipe_fd[i]);
		exec->child_pid = fork();
		exec->status = 0;
		if (exec->child_pid == -1)
			perror("fork"); // return int error ? E_FORK
		if (exec->child_pid == 0)
		{
			// printf("CHILD_PID [%d]\n", exec->child_pid);
			if (i == 0)
			{
				close(exec->pipe_fd[0][READ_END]);
				if (dup2(exec->pipe_fd[1][0], exec->pipe_fd[0][1]) == -1)
					return(EXIT_FAILURE);
			}
			if (i > 0 && i != data->nb_of_cmds)
			{
				if (dup2(exec->pipe_fd[i][WRITE_END], exec->pipe_fd[i - 1][READ_END]) == -1)
					return(EXIT_FAILURE);
				close(exec->pipe_fd[i][READ_END]);
			}
			if (i == data->nb_of_cmds)
			{
				if (dup2(STDIN_FILENO, exec->pipe_fd[i - 1][READ_END]) == -1)
					return(EXIT_FAILURE);
			}
			printf("COUCOU\n");
			if (data->cmd->is_builtin == false)
				execute_command(data);
			else
				ft_builtin(data);
		}
		else
		{
			waitpid(exec->child_pid, &exec->status, 0);
			if (WIFSIGNALED(exec->status))
				printf("^\\Quit: %d\n", SIGQUIT);
		}
	}
	return (EXIT_SUCCESS);
}
	// if (data->cmd->is_builtin == false)
	// 	ft_cmd_exec(data);
	// else
	// 	ft_builtin(data);
	// return (EXIT_SUCCESS);