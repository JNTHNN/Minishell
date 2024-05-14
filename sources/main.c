/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/05/03 11:22:34 by jgasparo         ###   ########.fr       */
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
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_handle_arg_error(argc, argv);
	ft_init_data(&data, envp);
	ft_init_signal();
	ft_minishell_loop(&data);
	ft_free_data(&data);
	return (EXIT_SUCCESS);
}
