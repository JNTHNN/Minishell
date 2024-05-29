/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:39:34 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/25 09:39:02 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Checks if character is a space or not.
*/
static bool	ft_check_space(char *arg)
{
	while (*arg && *arg != W_SPACE)
		arg++;
	if (*arg == '\0')
		return (false);
	return (true);
}

/*
** Allocates space for the new argument array
** if the first argument needs to be resplit.
*/
static int	ft_init_new_args(char **old, char **temp, char ***new)
{
	int		size;

	size = ft_tablen(temp) + ft_tablen((old));
	*new = (char **)malloc(size * sizeof(char *));
	if (!*new)
		return (E_MEM);
	return (EXIT_SUCCESS);
}

/*
** Fills the new argument array with resplited elements.
*/
static int	ft_fill_new_args(char **old, char **temp, char ***new)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ft_tablen(temp))
	{
		(*new)[i] = ft_strdup(temp[i]);
		if (!(*new)[i])
			return (free(*new), E_MEM);
	}
	j = 1;
	while (i < ft_tablen(old))
	{
		(*new)[i] = ft_strdup((old)[j]);
		if (!(*new)[i])
			return (free(*new), E_MEM);
		i++;
		j++;
	}
	(*new)[i] = NULL;
	return (EXIT_SUCCESS);
}

/*
** Resplits first argument if needed.
*/
int	ft_resplit_first_arg(char ***args)
{
	char	**temp_args;
	char	**new_args;

	if (!ft_check_space((*args)[0]))
		return (EXIT_SUCCESS);
	temp_args = ft_split((*args)[0], ' ');
	if (ft_init_new_args(*args, temp_args, &new_args))
		return (E_MEM);
	if (ft_fill_new_args(*args, temp_args, &new_args))
		return (E_MEM);
	ft_free_array((temp_args));
	ft_free_array((*args));
	(*args) = new_args;
	return (EXIT_SUCCESS);
}

/*
** Checks if the first argument of the array should be resplited.
*/
void	ft_should_resplit(char *arg, t_data *data)
{
	if (!arg || ft_count_all_quotes(arg))
		data->resplit = true;
}
