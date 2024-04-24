/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/23 22:43:21 by gdelvign         ###   ########.fr       */
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
		close(data->exec->tmpin);
		close(data->exec->tmpout);
		close(data->exec->fdin);
	}
	return (EXIT_SUCCESS);
}

t_redir_lst	*ft_find_last_redir(t_redir_lst **lst, t_redirect_type type)
{
	t_redir_lst	*is_last;
	t_redir_lst	*temp;

	is_last = NULL;
	if (!*lst)
		return (NULL);
	temp = *lst;
	while (temp)
	{
		if (temp->r_type == type)
			is_last = temp;
		temp = temp->next;
	}
	return (is_last);
}

int	ft_executor(t_data *data)
{
	t_exec		*exec;
	t_cmd		*current_cmd;
	t_redir_lst	*last;
	t_redir_lst	*last2;
	t_redir_lst	*last3;

	exec = (t_exec *)malloc(sizeof(t_exec));
	data->exec = exec;
	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	//if (data->redirections)
	exec->fdin = dup(exec->tmpin);
	if (data->nb_of_cmds == 1)
	{
		if (!data->cmd->is_builtin)
			ft_cmd_exec(data);
		else
			ft_builtin(data, data->cmd);
		dup2(exec->tmpin, STDIN_FILENO);
		dup2(exec->tmpout, STDOUT_FILENO);
		close(exec->tmpin);
		close(exec->tmpout);
		close(exec->fdin);
	}
	else
	{
		current_cmd = data->cmd;
		while (current_cmd)
		{
			if ((last = ft_find_last_redir(&current_cmd->redirections, HEREDOC)) != NULL)
				fprintf(stderr, "IS_LAST = %s / R_TYPE = %d\n", last->filename, last->r_type);
			if ((last2 = ft_find_last_redir(&current_cmd->redirections, IN)) != NULL)
				fprintf(stderr, "IS_LAST = %s / R_TYPE = %d\n", last2->filename, last2->r_type);
			if ((last3 = ft_find_last_redir(&current_cmd->redirections, OUT)) != NULL)
				fprintf(stderr, "IS_LAST = %s / R_TYPE = %d\n", last3->filename, last3->r_type);
			dup2(exec->fdin, STDIN_FILENO);
			close(exec->fdin);
			if (!current_cmd->right)
			{
				exec->fdout = dup(exec->tmpout); // ajouter outfile ici
			}
			else
			{
				pipe(exec->pipe_fd);
				exec->fdin = exec->pipe_fd[0];
				exec->fdout = exec->pipe_fd[1];
			}
			dup2(exec->fdout, STDOUT_FILENO);
			close(exec->fdout);
			exec->child_pid = fork();
			exec->status = 0;
			if (exec->child_pid == -1)
				perror("fork");
			if (exec->child_pid == 0)
			{
				if (!current_cmd->is_builtin)
					execute_command(data, current_cmd);
				else
					ft_builtin(data, current_cmd);
				exit(EXIT_SUCCESS);
			}
			current_cmd = current_cmd->right;
			waitpid(exec->child_pid, &exec->status, 0);
		}
		dup2(exec->tmpin, STDIN_FILENO);
		dup2(exec->tmpout, STDOUT_FILENO);
		close(exec->tmpin);
		close(exec->tmpout);
		close(exec->fdin);
		close(exec->fdout);
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
	}
	return (EXIT_SUCCESS);
}

