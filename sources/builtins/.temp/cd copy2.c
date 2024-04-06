/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:03:27 by jgasparo          #+#    #+#             */
/*   Updated: 2024/04/06 20:15:44 by jgasparo         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s1[i] > s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getenv(t_data *data, char *search)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], search, ft_strlen(search)))
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

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
	printf("NEW VAR [%s]\n", new_var);
    new_env[i] = ft_strdup(new_var);
    // Terminer le tableau avec NULL
    new_env[i + 1] = NULL;
    // Libérer l'ancien tableau
	ft_free_array(env);
	i = 0;
	while (new_env[i])
		printf("NEW_ENV [%s]\n", new_env[i++]);
    return (new_env);
}

// void	ft_oldpwd(t_data *data, char *oldpwd)
// {

// }

void	ft_seek_replace(t_data *data, char *search, char *pwd)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	// printf("SEEK [%s] | PWD [%s]\n", search, pwd);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], search, ft_strlen(search)))
		{
			// free(data->env[i]);
			data->env[i] = ft_strjoin(search, pwd);
			printf("J'AJOUTE CA [%s]\n", data->env[i]);
			found = 1;
		}
		i++;
	}
	if (!found)
		data->env = add_to_env(data->env, ft_strjoin(search, pwd));
}

void	ft_cd_home(t_data *data, char *pwd)
{
	char	*new_pwd;

	new_pwd = ft_getenv(data, "HOME=");
	printf("NEW_PWD POUR ENV [%s]\n", new_pwd);
	printf("OLD_PWD POUR ENV [%s]\n", pwd);
	ft_seek_replace(data, "PWD=", new_pwd + 5);
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
}

void	ft_cd_absolute(t_data *data, char *pwd)
{
	char	*new_pwd;

	new_pwd = data->cmd->args[1];
	if (!(ft_strlen(new_pwd) == 1) && new_pwd[ft_strlen(new_pwd) - 1] == '/') // si ca fini par / "cd /usr/"
		ft_memset(new_pwd + (ft_strlen(new_pwd) - 1), 0, 1); // magie noire j'adore
	printf("NEW_PWD [%s]\n", new_pwd);
	ft_seek_replace(data, "PWD=", data->cmd->args[1]);
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
}

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	**ft_append_pwd(char **pwd, char *path)
{
	int	i;
	char **append_pwd;

	i = 0;
	append_pwd = (char **)malloc(sizeof(char *) * ft_tablen(pwd) + 2);
	if (!append_pwd)
		return (NULL);
	while (pwd[i])
	{
		append_pwd[i] = ft_strdup(pwd[i]);
		i++;
	}
	append_pwd[i] = ft_strdup(path);
	append_pwd[i + 1] = NULL;
	// ft_free_array(pwd);
	return (append_pwd);
}

char	**ft_sup_pwd(char **pwd)
{
	char	**new_pwd;
	int		len;
	int		i;

	i = 0;
	len = ft_tablen(pwd);
	new_pwd = (char **)malloc(sizeof(char *) * (ft_tablen(pwd)));
	if (!new_pwd)
		return (NULL);
	while (i < len - 1)
	{
		new_pwd[i] = ft_strdup(pwd[i]);
		i++;
	}
	new_pwd[i] = NULL;
	ft_free_array(pwd);
	return (new_pwd);
}

char *ft_pwdcat(char **pwd)
{
	char	*new_pwd;
	int		i;

	i = 0;
	new_pwd = ft_strdup("");
	while (pwd[i])
	{
		new_pwd = ft_strjoin(new_pwd, "/");
		new_pwd = ft_strjoin(new_pwd, pwd[i]);
		i++;
	}
	return (new_pwd);
}

void	ft_cd_relative(t_data *data, char *pwd)
{
	char	**temp_path;
	char	**temp_pwd;
	int		i;
	
	temp_path = ft_split(data->cmd->args[1], '/');
	temp_pwd = ft_split(pwd, '/');
	i = 0;
	while (temp_path[i])
	{
		printf("TEMP_PATH WHILE [%s]\n", temp_path[i]);
		printf("RESULTAT STRNCMP [%d] ET STRCMP [%d]\n", ft_strncmp(temp_path[i], ".", 2), ft_strcmp(temp_path[i], "."));
		if (!ft_strncmp(temp_path[i], "..", 2)) // donc si "cd .." ou "cd libft/../libft"
		{
			printf("CONDITION .. \n");
			printf("TEMP_PATH [%s]\n", temp_path[i]);
			temp_pwd = ft_sup_pwd(temp_pwd);
			// j = ft_tablen(temp_pwd);
			// ft_memset(temp_pwd[j - 1], 0, ft_strlen(temp_pwd[j - 1])); // j'efface la ligne en question
			// new_pwd = ft_strdup("");
			// j = 0;
		}
		else if (ft_strncmp(temp_path[i], ".", 2) != 0) // si "cd ." ou "cd ./includes/./includes"
		{
			printf("CONDITiON . \n");
			printf(" . TEMP_PATH [%s]\n", temp_path[i]);
			temp_pwd = ft_append_pwd(temp_pwd, temp_path[i]);
			printf(" . CHECK A_PWD APRES [%s]\n", temp_pwd[ft_tablen(temp_pwd) - 1]);
		}
		i++;
	}
	ft_seek_replace(data, "PWD=", ft_pwdcat(temp_pwd + 1));
	printf("RELATIVE PWD [%s]\n", ft_pwdcat(temp_pwd + 1));
	ft_seek_replace(data, "OLDPWD=", pwd + 4);
	printf("RELATIVE OLDPWD [%s]\n", pwd);
}

void	ft_change_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_getenv(data, "PWD");
	printf("TEST PWD GETENV [%s]\n", pwd);
	if (!pwd)
		ft_putstr_fd("No PWD, No party\n", STDERR_FILENO);
	if (!data->cmd->args[1]) // path home == "cd"
	{
		printf("JE PASSE DANS LA COND ARG[1]\n");
		ft_cd_home(data, pwd);
	}
	else if (data->cmd->args[1][0] == '/') // path absolu == "cd /nomdudoss"
	{
		printf("JE PASSE DANS LA COND /\n");
		ft_cd_absolute(data, pwd);
	}
	else // la classique "cd sources/builtins"
	{
		printf("JE PASSE DANS LA COND ELSE\n");
		ft_cd_relative(data, pwd);
		printf("PWD [%s]\n", pwd);
		printf("PATH [%s]\n", data->cmd->args[1]);
	}
}


int	ft_check_dir(t_data *data)
{
	// je dois recuperer la var $HOME
	// puis rediriger labas en modifiant PWD et OLD_PWD
	char *home;

	home = ft_getenv(data, "HOME=");
	if (!home)
	{
		perror("No HOME, No party");
		return (0);
	}
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
	}
	// printf("OLD_PWD [%s]\n", ft_getenv(data, "OLDPWD="));
}
