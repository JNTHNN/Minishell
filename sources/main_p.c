/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:18 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/17 11:59:01 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

static void	ft_init_data(t_data *data, char **envp)
{
	(void)envp;
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
}

static int	ft_get_input(t_data *data)
{
	ft_init_signal();
	data->input = readline(PROMPT);
	ft_get_ctrl_d(data);
	if (ft_trim_input(&data->input))
		return (E_MEM);
	return (EXIT_SUCCESS);
}

static int	ft_minishell_loop(t_data *data)
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
    return 0;
}

static int	ft_get_test_input(t_data *data, char *input)
{
	data->input = input;
	if (ft_trim_input(&data->input))
		return (E_MEM);
	return (EXIT_SUCCESS);
}

static int	ft_minishell_test_mode(t_data *data, char **arg_input)
{
    int     i;
	int		ret;

    i = 0;
	while (arg_input[i])
	{
		ret = ft_get_test_input(data, arg_input[i]);
		if (ft_handle_error(data, ret))
			continue ;
		if (data->input && data->input[0])
		{
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
        i++;
	}
    return 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
    char	**arg_input;

    if (argc == 3 && ft_strncmp(argv[1], "-c", 2) == 0 && argv[2])
	{
		arg_input = ft_split(argv[2], ';');
		if (!arg_input)
            exit(EXIT_FAILURE);
		ft_init_data(&data, envp);
        ft_minishell_test_mode(&data, arg_input);
	    /* ft_free_data(&data); */
    }
    else {
		ft_handle_arg_error(argc, argv);
		ft_init_data(&data, envp);
		ft_minishell_loop(&data);
		ft_free_data(&data);
    }
	return (EXIT_SUCCESS);
}
