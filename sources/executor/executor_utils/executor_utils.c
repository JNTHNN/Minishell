/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:15 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/13 22:33:22 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_check_exe(char *dir)
// {
// 	struct stat	s_stat;

// 	if (lstat(dir, &s_stat) < 0)
	
// }

// bash-3.2$ eee
// bash: eee: command not found
// bash-3.2$ echo $?
// 127
// bash-3.2$ /etc
// bash: /etc: is a directory
// bash-3.2$ echo $?
// 126
// bash-3.2$ ./minishell_tester/test_files/invalid_permission
// bash: ./minishell_tester/test_files/invalid_permission: Permission denied
// bash-3.2$ echo $?
// 126

void	execute_command(t_data *data, t_cmd *cmd)
{
	struct stat	s_stat;

	if (cmd->args)
	{
		if (!ft_strncmp(cmd->args[0], "/", 1)
			|| !ft_strncmp(cmd->args[0], "./", 2)) // si ca commence par ./exe ou /exe 126
		{
			if (lstat(cmd->args[0], &s_stat) < 0)
				ft_errno(cmd->args[0], 127, data);
			if (S_ISDIR(s_stat.st_mode))
			{
				ft_errno(cmd->args[0], 126, data);
			}
			else
			{
				if (execve(cmd->args[0], cmd->args, data->env) == -1)
				{
					perror("execve absolu");
					exit(EXIT_FAILURE);
				}
			}
		}
		else // direct exe
		{
			if (ft_create_exec(data, cmd))
				ft_errno_exec(data, cmd->args[0]);
		}
	}
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
	int		i;

	progpath = ft_path_abs(data, cmd);
	i = 0;
	if (!progpath)
		return (EXIT_FAILURE);
	while (progpath[i])
	{
		if (access(progpath[i], F_OK) == 0)
		{
			if (execve(progpath[i], cmd->args, data->env) == -1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	ft_free_array(progpath);
	return (EXIT_FAILURE);
}

t_exec	*ft_init_exec(t_data *data)
{
	t_exec		*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		ft_errno(ERR_MEM, 2, data);
	exec->child_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_cmds);
	if (!exec->child_pid)
		ft_errno(ERR_MEM, 2, data);
	exec->status = -1;
	exec->tmpin = -1;
	exec->tmpout = -1;
	exec->fdin = -1;
	exec->fdout = -1;
	exec->trigger_hd = false;
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