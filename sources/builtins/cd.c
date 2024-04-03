/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/03 21:08:52 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GERER TOUT LES RACCOURCIS
// CD SANS ARGS -> $HOME
// CD - -> OLD_PWD
// CD ~ -> $HOME
// CD .. -> REPERTOIRE PARENT
// CD / -> RACINE SYSTEME
// CD . -> RIEN REPERTOIRE ACTUEL
// CD ~user -> REPERTOIRE PERSO DE L'USER SPECIFIE
// UNSET PWD NE FAIT RIEN MAIS EN CREE UN APRES L'ACTION DE CD

// doit faire l'expand de ..

// tab de tab + recursive strrchr + memset

#include <stdlib.h>
#include <string.h>

char **add_to_env(char **env, char *new_var)
{
    int i = 0;
	int	j = 0;
    char **new_env;

    // Compter le nombre de lignes dans env
    while (env[i])
        i++;
    // Allouer un nouveau tableau avec une ligne supplémentaire
    new_env = malloc((i + 2) * sizeof(char *));
    if (!new_env)
        return (NULL);
    // Copier les lignes existantes
	printf("I [%d]\n", i);
  	while (j < i)
	{
        new_env[j] = ft_strdup(env[j]);
		j++;
	}
    // Ajouter la nouvelle variable
    new_env[i] = ft_strdup(new_var);
    // Terminer le tableau avec NULL
    new_env[i + 1] = NULL;
    // Libérer l'ancien tableau
	ft_free_array(env);
    return (new_env);
}

void	ft_change_pwd(t_data *data)
{
	char	*pwd;
	char	*new_pwd;
	int		i;

	i = 0;
	pwd = getenv("PWD");
	if (!pwd)
		ft_putstr_fd("No PWD, No party\n", STDERR_FILENO);
	if (!data->cmd->args[1])
	{
		// je dois aller au chemin de HOME et mettre ma pos actuelle dans OLD_PWD
		new_pwd = getenv("HOME");
		// je dois acceder a la var PWD dans l'env
		while (data->env[i])
		{
			if (!ft_strncmp(data->env[i], "PWD=", 4))
				data->env[i] = ft_strjoin("PWD=", new_pwd);
			i++;
		}
	}
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "OLD_PWD=", 8))
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin("OLD_PWD=", pwd);;
		}
		i++;
	}
	printf("OLD_PWD [%s]\n", pwd);
	data->env = add_to_env(data->env, ft_strjoin("OLD_PWD=", pwd));

}

// void	ft_change_old_pwd(t_data *data)
// {
	
// }

int	ft_check_dir(t_data *data)
{
	// je dois recuperer la var $HOME
	// puis rediriger labas en modifiant PWD et OLD_PWD
	char *home;

	home = getenv("HOME");
	if (data->cmd->args[1])
	{
		if (!data->cmd->args[1] && chdir(home) == -1)
		{
			perror("cd home");
			return (0);
		}
		else if (chdir(data->cmd->args[1]) == -1)
		{
			perror("cd direction");
			return (0);
		}
	}
	return (1);
}

void	ft_cd(t_data *data)
{
	// j'ai besoin de PWD / OLD_PWD / HOME
	if (ft_check_dir(data))
	{
		ft_change_pwd(data);
		// ft_change_old_pwd(data);
	}
}
