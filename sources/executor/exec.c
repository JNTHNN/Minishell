/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/19 11:10:28 by jgasparo         ###   ########.fr       */
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
		execute_command(data, data->cmd);
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
		// if (ft_find_last_redir(&data->cmd->redirections, HEREDOC))
		// 	pipe(exec->pipe_fd[0]);
		if (!data->cmd->is_builtin)
			return (ft_cmd_exec(data));
		else
			return (ft_builtin(data, data->cmd));
	}
	// if (data->nb_of_cmds > 1)
	// {
	// 	i = -1;
	// 	while (++i < data->nb_of_cmds)
	// 	{
	// 		fprintf(stderr, "NB OF MALLOC PIPE [%d]\n", i);
	// 		exec->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
	// 		pipe(exec->pipe_fd[i]);
	// 	}
	// 	i = -1;
	// 	// while (++i < data->nb_of_cmds)
	// 	while (data->cmd)
	// 	{
	// 		exec->child_pid = fork();
	// 		exec->status = 0;
	// 		if (exec->child_pid < 0)
	// 			perror("fork");
	// 		if (exec->child_pid == 0)
	// 		{
	// 			close(exec->pipe_fd[0][1]);
	// 			close(exec->pipe_fd[1][0]);
	// 			close(exec->pipe_fd[1][1]);
	// 			if (data->cmd->is_builtin == false)
	// 				execute_command(data, data->cmd);
	// 			else
	// 				ft_builtin(data, data->cmd);
	// 			close(exec->pipe_fd[0][0]);

	// 		}
	// 		close(exec->pipe_fd[0][0]);
	// 		close(exec->pipe_fd[0][1]);
	// 		close(exec->pipe_fd[1][0]);
	// 		close(exec->pipe_fd[1][1]);
	// 		waitpid(exec->child_pid, &exec->status, 0);
	// 		if (WIFSIGNALED(exec->status))
	// 			printf("^\\Quit: %d\n", SIGQUIT);
	// 		data->cmd = data->cmd->right;
	// 	}
	// }
	// return (EXIT_SUCCESS);
	i = -1;
	while (++i < data->nb_of_cmds - 1)
	{
		fprintf(stderr, "NB OF MALLOC PIPE [%d]\n", i);
		exec->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(exec->pipe_fd[i]) < 0)
		{
			perror("pipe");
			return EXIT_FAILURE;
		}
	}

	i = -1;
	while (data->cmd)
	{
		exec->child_pid = fork();
		exec->status = 0;
		if (exec->child_pid < 0)
		{
			perror("fork");
			return EXIT_FAILURE;
		}
		if (exec->child_pid == 0)
		{
			if (i != -1)
			{
				dup2(exec->pipe_fd[i][0], 0);
				close(exec->pipe_fd[i][0]);
				close(exec->pipe_fd[i][1]);
			}
			if (data->cmd->right)
			{
				dup2(exec->pipe_fd[i + 1][1], 1);
				close(exec->pipe_fd[i + 1][0]);
				close(exec->pipe_fd[i + 1][1]);
			}
			if (data->cmd->is_builtin == false)
				execute_command(data, data->cmd);
			else
				ft_builtin(data, data->cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (i != -1)
			{
				close(exec->pipe_fd[i][0]);
				close(exec->pipe_fd[i][1]);
			}
			waitpid(exec->child_pid, &exec->status, 0);
			if (WIFSIGNALED(exec->status))
				printf("^\\Quit: %d\n", SIGQUIT);
			if (data->cmd)
				data->cmd = data->cmd->right;
			i++;
		}
	}
	if (i != -1 && i < data->nb_of_cmds - 1)
	{
		close(exec->pipe_fd[i][0]);
		close(exec->pipe_fd[i][1]);
	}
	return (EXIT_SUCCESS);
}

