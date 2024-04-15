/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:37 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/15 20:50:37 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_pathiter(char **path, t_data *data)
{
	char	*new_cmd;
	char	*temp;

	new_cmd = ft_strjoin("/", data->cmd->args[0]);
	while (*path)
	{
		temp = ft_strjoin(*path, new_cmd);
		*path = temp;
		path++;
	}
	return (path);
}

static char	**ft_path_abs(t_data *data)
{
	char	*path;
	char	**my_path;

	path = getenv("PATH");
	my_path = ft_split(path, ':');
	ft_pathiter(my_path, data);
	return (my_path);
}

static int	ft_create_exec(t_data *data)
{
	char	**progpath;

	progpath = ft_path_abs(data);
	if (!progpath)
	{
		perror("path");
		exit(EXIT_FAILURE);
	}
	while (*progpath)
	{
		if (access(*progpath, F_OK) == 0)
		{
			if (execve(*progpath, data->cmd->args, data->env) == -1)
			{
				perror("command");
				exit(EXIT_FAILURE);
			}
		}
		progpath++;
	}
	return (EXIT_FAILURE);
}

/*	On fork	
**	PID == -1 : ERROR
**	SI LE FORK REUSSIT, LE PROCESSUS PERE ATTEND LE PROCESSUS FILS
**	PID > 0 :  ON BLOCK LE PROCESSUS PERE JUSQU'A QUE L'ENFANT TERMINE (WAITPID)
**	PUIS ON KILL LE PROCESSUS ENFANT
**	ELSE (PID == 0) : LE PROCESSUS ENFANT EXECUTE LA COMMANDE
*/

static void	execute_command(t_data *data)
{
	if (!ft_strncmp(data->cmd->args[0], "/", 1)
		|| !ft_strncmp(data->cmd->args[0], "./", 2))
	{
		if (execve(data->cmd->args[0], data->cmd->args, data->env) == -1)
		{
			perror("execve absolu");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (ft_create_exec(data) == EXIT_FAILURE)
		{
			perror("command not found");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

void	ft_cmd_exec(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		execute_command(data);
}

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