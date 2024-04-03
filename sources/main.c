/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:49 by anvoets           #+#    #+#             */
/*   Updated: 2024/04/03 09:17:16 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		ret;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd(ERR_ARG, STDERR_FILENO);
		exit(0);
	}
	data.env = ft_envcpy(envp);
	data.cmd = NULL;
	ft_init_signal();
	while (true)
	{
		data.input = readline(PROMPT);
		if (ft_trim_input(&data.input))
			return (E_MEM);
		if (data.input && data.input[0])
		{
			add_history(data.input);
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
			if (ft_is_builtin(data.cmd->args[0]) == false)
				ft_cmd_exec(&data);
			else
				ft_builtin(&data);
			ft_reset_data(&data);
		}
		ft_signal();
	}
	return (EXIT_SUCCESS);
}
