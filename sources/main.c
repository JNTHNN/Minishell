/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/04/15 11:49:11 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		ret;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(0);
	}
	ft_init_signal();
	data.env = ft_envcpy(envp);
	data.cmd = NULL;
	data.hist = ft_create_hist();
	data.is_itoa = false;
	while (true)
	{
		data.input = readline(PROMPT);
		ft_get_ctrl_d(&data);
		if (ft_trim_input(&data.input))
			return (E_MEM);
		if (data.input && data.input[0])
		{
			ft_fill_local_history(&data);
			add_history(data.input);
			if (ft_strlen(data.input) == 2 && !ft_strncmp(data.input, "!!", 2))
			{
				if (data.hist->lastline)
				{
					free(data.input);
					data.input = ft_strdup(data.hist->lastline);
				}
			}
			ret = ft_tokenize(&data);
			if (ret)
			{
				ft_throw_error(&data, ret);
				continue ;
			}
			free(data.input);
			ret = ft_parse(&data);
			if (ret)
			{
				ft_throw_error(&data, ret);
				continue ;
			}
			ret = ft_expand(&data);
			if (ret)
			{
				ft_throw_error(&data, ret);
				continue ;
			}
			if (data.cmd->is_builtin == false)
				ft_cmd_exec(&data);
			else
				ft_builtin(&data);
			ft_reset_data(&data);
		}
		ft_signal();
	}
	return (EXIT_SUCCESS);
}
