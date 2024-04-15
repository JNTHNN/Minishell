/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/04/15 15:33:50 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code = 0;

static void	ft_handle_arg_error(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(0);
	}
}

static void	ft_init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->hist = ft_create_hist();
	data->env = ft_envcpy(envp);
	data->tokens = NULL;
	data->cmd = NULL;
	data->redirections = NULL;
	data->is_itoa = false;
}

static void	ft_handle_history(t_data *data)
{
	ft_fill_local_history(data);
	add_history(data->input);
	if (ft_strlen(data->input) == 2 && !ft_strncmp(data->input, "!!", 2))
	{
		if (data->hist->lastline)
		{
			free(data->input);
			data->input = ft_strdup(data->hist->lastline);
		}
	}
}

static int	ft_get_input(t_data *data)
{
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
		if (ret)
		{
			ft_throw_error(data, ret);
			continue ;
		}
		if (data->input && data->input[0])
		{
			ft_handle_history(data);
			ret = ft_tokenize(data);
			if (ret)
			{
				ft_throw_error(data, ret);
				continue ;
			}
			free(data->input);
			ret = ft_parse(data);
			if (ret)
			{
				ft_throw_error(data, ret);
				continue ;
			}
			ret = ft_expand(data);
			if (ret)
			{
				ft_throw_error(data, ret);
				continue ;
			}
			if (data->cmd->is_builtin == false)
				ft_cmd_exec(data);
			else
				ft_builtin(data);
			ft_reset_data(data);
		}
		ft_signal();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_handle_arg_error(argc, argv);
	ft_init_signal();
	ft_init_data(&data, envp);
	ft_minishell_loop(&data);
	return (EXIT_SUCCESS);
}
