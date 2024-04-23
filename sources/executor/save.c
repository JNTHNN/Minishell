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

#include <fcntl.h>
#include <errno.h>

int is_fd_open(int fd)
{
	return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

int	ft_executor(t_data *data)
{
	t_exec	*exec;
	t_cmd	*current_cmd;
	int		i;
	int		j;

	// Allocation de la structure exec et du tableau de pipe_fd et du tableau de child_pid
	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->pipe_fd = (int **)malloc(sizeof(int *) * data->nb_of_cmds);
	exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
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
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		exec->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(exec->pipe_fd[i]) == -1)
			perror("pipe");
	}
	// Itrération sur les commandes de la liste chainée
	current_cmd = data->cmd;
	i = 0;
	while (current_cmd)
	{
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
				if (dup2(exec->pipe_fd[i - 1][READ_END], STDIN_FILENO) == -1)
					fprintf(stderr, " ERROR ICI ERRNO : %d\n", errno);
				close(exec->pipe_fd[i - 1][WRITE_END]);
			}
			// S'il y a une commande après
			if (current_cmd->right)
			{
				 if (dup2(exec->pipe_fd[i][WRITE_END], STDOUT_FILENO == -1))
					fprintf(stderr, " ERROR LA ERRNO : %d\n", errno);
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
			if (!current_cmd->is_builtin)
			{
				fprintf(stderr, "COMMANDE [%s] \n", current_cmd->args[0]);
				execute_command(data, current_cmd);
			}
			else
			{
				fprintf(stderr, "COMMANDE [%s] \n", current_cmd->args[0]);
				ft_builtin(data, current_cmd);
			}
			exit(EXIT_SUCCESS);
		}
		current_cmd = current_cmd->right;
		i++;
	}
	// Fermer tous les pipes du parent
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		close(exec->pipe_fd[i][READ_END]);
		close(exec->pipe_fd[i][WRITE_END]);
	}
	// PARENT
	// Attendre tous les enfants
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		fprintf(stderr, "STATUS %d\n", exec->status);
		waitpid(exec->child_pid[i], &exec->status, 0);
		if (WIFSIGNALED(exec->status))
			perror("exit");
		// printf("^\\Quit: %d\n", SIGQUIT);
	}
	i = -1;
	while (++i < data->nb_of_cmds)
	{
		int j = 0;
		while (j < 2)
		{
			if (is_fd_open(exec->pipe_fd[i][j]))
			{
				printf("Le descripteur de fichier %d est ouvert. [%d][%d]\n", exec->pipe_fd[i][j], i, j);
			}
			else
			{
				printf("Le descripteur de fichier %d n'est pas ouvert. [%d][%d]\n", exec->pipe_fd[i][j], i, j);
			}
			j++;
		}
	}
	return (EXIT_SUCCESS);
}


// int	ft_executor(t_data *data)
// {
// 	t_exec	*exec;
// 	int		i;


// 	exec = (t_exec *)malloc(sizeof(t_exec));
// 	exec->pipe_fd = (int **)malloc(sizeof(int *) * data->nb_of_cmds);

// 	if (data->nb_of_cmds == 1)
// 	{
// 		exec->pipe_fd[0] = (int *)malloc(sizeof(int) * 2);
// 		// if (ft_find_last_redir(&data->cmd->redirections, HEREDOC))
// 		// 	pipe(exec->pipe_fd[0]);
// 		if (!data->cmd->is_builtin)
// 			return (ft_cmd_exec(data));
// 		else
// 			return (ft_builtin(data, data->cmd));
// 	}
// 	i = -1;
// 	while (data->cmd)
// 	{
// 		exec->child_pid = fork();
// 		exec->status = 0;
// 		if (exec->child_pid < 0)
// 		{
// 			perror("fork");
// 			return EXIT_FAILURE;
// 		}
// 		if (exec->child_pid == 0)
// 		{
// 			if (i != -1)
// 			{
// 				dup2(exec->pipe_fd[i][0], 0);
// 				close(exec->pipe_fd[i][0]);
// 				close(exec->pipe_fd[i][1]);
// 			}
// 			if (data->cmd->right)
// 			{
// 				dup2(exec->pipe_fd[i + 1][1], 1);
// 				close(exec->pipe_fd[i + 1][0]);
// 				close(exec->pipe_fd[i + 1][1]);
// 			}
// 			if (data->cmd->is_builtin == false)
// 				execute_command(data, data->cmd);
// 			else
// 				ft_builtin(data, data->cmd);
// 			exit(EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			if (i != -1)
// 			{
// 				close(exec->pipe_fd[i][0]);
// 				close(exec->pipe_fd[i][1]);
// 			}
// 			waitpid(exec->child_pid, &exec->status, 0);
// 			if (WIFSIGNALED(exec->status))
// 				printf("^\\Quit: %d\n", SIGQUIT);
// 			if (data->cmd)
// 				data->cmd = data->cmd->right;
// 			i++;
// 		}
// 	}
// 	if (i != -1 && i < data->nb_of_cmds - 1)
// 	{
// 		close(exec->pipe_fd[i][0]);
// 		close(exec->pipe_fd[i][1]);
// 	}
// 	return (EXIT_SUCCESS);
// }