/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/29 16:18:05 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_data *data, t_cmd *cmd)
{
	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], "/", 1)
			|| !ft_strncmp(cmd->args[0], "./", 2))
		{
			if (execve(cmd->args[0], cmd->args, data->env) == -1)
			{
				perror("execve absolu");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (ft_create_exec(data, cmd) == EXIT_FAILURE)
			{
				perror("command not found");
				exit(EXIT_FAILURE);
			}
		}
	}
	exit(EXIT_SUCCESS);
}

char	**ft_pathiter(char **path, t_cmd *cmd)
{
	char	*new_cmd;
	char	*temp;

	new_cmd = ft_strjoin("/", cmd->args[0]);
	while (path && *path)
	{
		temp = ft_strjoin(*path, new_cmd);
		*path = temp;
		path++;
	}
	return (path);
}

char	**ft_path_abs(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**my_path;

	path = ft_getenv(data, "PATH");
	my_path = ft_split(path, ':');
	ft_pathiter(my_path, cmd);
	return (my_path);
}

int	ft_create_exec(t_data *data, t_cmd *cmd)
{
	char	**progpath;

	progpath = ft_path_abs(data, cmd);
	if (!progpath)
	{
		perror("path");
		exit(EXIT_FAILURE);
	}
	while (*progpath)
	{
		if (access(*progpath, F_OK) == 0)
		{
			if (execve(*progpath, cmd->args, data->env) == -1)
			{
				perror("command");
				exit(EXIT_FAILURE);
			}
		}
		progpath++;
	}
	return (EXIT_FAILURE);
}

t_exec	*ft_init_exec(t_data *data)
{
	t_exec		*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
	if (!exec->child_pid)
		return (NULL);
	exec->status = -1;
	exec->tmpin = -1;
	exec->tmpout = -1;
	exec->fdin = -1;
	exec->fdout = -1;
	exec->last_r = (t_last_redir *)malloc(sizeof(t_last_redir));
	if (!exec->last_r)
		return (NULL);
	exec->last_r->in = NULL;
	exec->last_r->out = NULL;
	exec->last_r->out_t = NULL;
	exec->last_r->hd = NULL;
	data->exec = exec;
	return (exec);
}

/*	On fork	
**	PID == -1 : ERROR
**	SI LE FORK REUSSIT, LE PROCESSUS PERE ATTEND LE PROCESSUS FILS
**	PID > 0 :  ON BLOCK LE PROCESSUS PERE JUSQU'A QUE L'ENFANT TERMINE (WAITPID)
**	PUIS ON KILL LE PROCESSUS ENFANT
**	ELSE (PID == 0) : LE PROCESSUS ENFANT EXECUTE LA COMMANDE
*/

/*	CREER UN FLAG POUR CREAT_EXEC SI -1 DNC PAS DE COMMANDE
**	-> EXIT POUR KILL LE PROCESSUS
*/

/*	REDIRECTION '>'
**	CHECKER LE FICHIER INDIQUE APRES LA REDIR
**	SI N'EXISTE PAS -> CREER
**	SI EXISTE -> CHECKER LES DROITS
**	OPEN LE FICHIER
**	REMPLACER LE FD STDOUT PAR LE FD DU FICHIER
**	ECRASE LES DONNEES EXISTANTES
**	CASE : echo A >B>C>D -> CREE B C D ET ECRIT QUE DANS D
**	echo test >file test1 -> ECRIT test test1 DANS FILE
*/

/*	REDIRECTION '>>'
**	CHECKER LE FICHIER INDIQUE APRES LA REDIR
**	SI N'EXISTE PAS -> CREER
**	SI EXISTE -> CHECKER LES DROITS
**	OPEN LE FICHIER
**	REMPLACER LE FD STDOUT PAR LE FD DU FICHIER
**	ECRIT A LA SUITE DES DONNEES SI IL Y'EN A	
*/

/*	REDIRECTION '<'
**	CHECKER LE FICHIER INDIQUE APRES LA REDIR
**	SI N'EXISTE PAS -> ERROR
**	SI EXISTE -> CHECKER LES DROITS
**	OPEN LE FICHIER
**	REMPLACER LE FD STDIN PAR LE FD DU FICHIER
*/

/*	REDIRECTION '<<'
**	UTILISATION DU HEREDOC
**	L'ARG APRES LA REDIR EST LE 'DELIMITEUR'
**	
*/