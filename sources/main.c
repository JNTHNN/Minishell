/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:18 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/15 15:42:23 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Unique global variable declaration.
*/
int	g_exit_code = 0;

/*
** Increments the SHLVL environment variable by 1 
** each time a minishell is launched.
*/
static void	ft_increment_shlvl(char **env)
{
	int		i;
	char	*shlvl_val;
	int		i_val;
	char	*new_str;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			shlvl_val = ft_strdup(ft_strchr(env[i], '=') + 1);
			i_val = ft_atoi(shlvl_val);
			free(shlvl_val);
			i_val++;
			shlvl_val = ft_itoa(i_val);
			new_str = ft_strjoin("SHLVL=", shlvl_val);
			free(shlvl_val);
			free(env[i]);
			env[i] = new_str;
		}
	}
}

/*
** Initializes the data structure with all useful variables ans structures.
*/
static void	ft_init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->tokens = NULL;
	data->cmd = NULL;
	data->redirections = NULL;
	data->is_itoa = false;
	data->resplit = false;
	data->nb_of_cmds = 0;
	data->exec = NULL;
	data->err_info = NULL;
	data->hist = ft_create_hist();
	data->env = ft_envcpy(envp);
	if (!data->hist || !data->env)
	{
		ft_handle_error(data, E_MEM);
		errno = ENOMEM;
		exit(errno);
	}
	ft_increment_shlvl(data->env);
}

/*
** Reads input from the user and handles end-of-file conditions.
*/
static int	ft_get_input(t_data *data)
{
	ft_init_signal();
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	data->input = readline(PROMPT);
	ft_get_ctrl_d(data);
	if (ft_trim_input(&data->input))
		return (E_MEM);
	return (EXIT_SUCCESS);
}

/* 
** Main execution loop that processes user input and handles commands. 
*/
static void	ft_minishell_loop(t_data *data)
{
	int		ret;

	while (true)
	{
		ret = ft_get_input(data);
		if (ft_handle_error(data, ret))
			continue ;
		if (data->input && data->input[0])
		{
			ft_handle_history(data);
			ret = ft_tokenize(data);
			if (ft_handle_error(data, ret))
				continue ;
			ret = ft_parse(data);
			if (ft_handle_error(data, ret))
				continue ;
			ret = ft_expand(data);
			if (ft_handle_error(data, ret))
				continue ;
			ret = ft_executor(data);
			if (ft_handle_error(data, ret))
				continue ;
			ft_reset_data(data);
		}
	}
}

/* 
**  Program initialization and entry point for the minishell.
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_handle_arg_error(argc, argv);
	ft_init_data(&data, envp);
	ft_minishell_loop(&data);
	ft_free_data(&data);
	return (EXIT_SUCCESS);
}
