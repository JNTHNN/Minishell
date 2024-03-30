/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/30 23:02:28 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	# check each arg from (the array of) cmd node
	# check if there are quotes and which type
	# check if there is a $ (inside of quotes or not)
	# expand the variable if it is in double quotes or not in quotes,
	which means replace it by its value taken from the env or the global variable
	# remove all quotes
*/

/*
	count quotes
	if quotes, get indexes
	check for $ and get index (several possible...)
	check quote types
	are they between double quotes ? => expand
	remove all quotes 
*/

/*
	array of struct with quote index and type ???
*/

bool	ft_is_expand_char(char c)
{
	if (c == DBL_Q || c == SGL_Q || c == DOLLAR)
		return (true);
	return (false);
}

int	ft_count_expand_char(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == DBL_Q || *str == SGL_Q || *str == DOLLAR)
			i++;
		str++;
	}
	return (i);
}


// char	ft_define_quotes_type(char *str)
// {
// 	if (ft_strchr(str, DBL_Q))
	
// }

int	*ft_find_quotes_idx(char *str)
{
	t_expand	*arr_idx;
	int			exp_char_nb;
	int			i;
	char		*start;

	start = str;
	exp_char_nb = ft_count_expand_char(str);
	if (exp_char_nb == 0)
		return (0);
	arr_idx = (t_expand *)malloc(exp_char_nb * sizeof(t_expand));
	if (!arr_idx)
		return (E_MEM);
	i = -1;
	while (++i < exp_char_nb)
		arr_idx[i].id = -1;
	i = 0;
	while (*str)
	{
		if (ft_is_expand_char(*str))
		{
			if (*str == DBL_Q)
				arr_idx[i].char_type = DBL_Q;
			else if (*str == SGL_Q)
				arr_idx[i].char_type = SGL_Q;
			else if (*str == DOLLAR)
				arr_idx[i].char_type = DOLLAR;
			arr_idx[i].position = str - start;
			arr_idx[i].id = i;
			i++;
		}
		str++;
	}
	if (arr_idx[0].id == -1)
		return (-1);
	return (EXIT_SUCCESS);
}


int	ft_expand(t_data *data)
{
	t_cmd	*current;
	int		i;

	current = data->cmd;
	while (current)
	{
		printf("CMD %i\n", current->id);
		i = 0;
		while (current->args[i])
		{
			printf("%s\n", current->args[i]);
			printf("%i\n", ft_count_quotes_and_doll(current->args[i]));
			i++;
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
