/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/19 17:17:07 by gdelvign         ###   ########.fr       */
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
	t_cmd	*current_cmd;
	int		i;
	int		j;

	// Allocation de la structure exec et du tableau de pipe_fd et du tableau de child_pid
	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
	exec->tmp_std[IN] = dup(STDIN_FILENO);
	exec->tmp_std[OUT] = dup(STDOUT_FILENO);
	exec->pipe_fd[READ_END] = dup(exec->tmp_std[IN]);
	// Itrération sur les commandes de la liste chainée
	current_cmd = data->cmd;
	i = 0;
	while (current_cmd)
	{
		dup2(exec->pipe_fd[READ_END], STDIN_FILENO);
		close(exec->pipe_fd[READ_END]);
		if (!current_cmd->right)
			exec->pipe_fd[WRITE_END] = dup(exec->tmp_std[OUT]);
		else
		{
			
		}
		
		exec->child_pid[i] = fork();
		exec->status = 0;
		if (exec->child_pid[i] == -1)
			perror("fork");
		// ENFANT
		// Si on est dans le processus enfant
		if (exec->child_pid[i] == 0)
		{
			// Si on est pas dans la 1re commande
			if (i > 0)
			{
			}
			// S'il y a une commande après
			if (current_cmd->right)
			{
				dup2(exec->pipe_fd[i][WRITE_END], STDOUT_FILENO);
				close(exec->pipe_fd[i][READ_END]);
			}
			// Fermer tous les autres pipes
			j = -1;
			while (++j < data->nb_of_cmds)
			{
				if (j != i - 1)
					close(exec->pipe_fd[j][READ_END]);
				if (j != i)
					close(exec->pipe_fd[j][WRITE_END]);
			}
			// Exécution da la commande ou du builtin
			if (!data->cmd->is_builtin)
				execute_command(data, current_cmd);
			else
				ft_builtin(data, current_cmd);
			exit(EXIT_SUCCESS);
		}
		current_cmd = current_cmd->right;
		i++;
	}
	// PARENT
	// Fermer tous les pipes du parent
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		close(exec->pipe_fd[i][READ_END]);
		close(exec->pipe_fd[i][WRITE_END]);
	}
	// Attendre tous les enfants
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		waitpid(exec->child_pid[i], &exec->status, 0);
		if (WIFSIGNALED(exec->status))
			perror("exit");
		// printf("^\\Quit: %d\n", SIGQUIT);
	}
	return (EXIT_SUCCESS);
}
