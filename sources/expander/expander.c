/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/29 23:30:30 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	# check each arg from (the array of) each from each cmd node
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
	define quote types
	are they between double quotes ? => expand
	remove all quotes 
*/

/*
	array of struct with quote index and type ???
*/

int	ft_count_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == DBL_Q || *str == SGL_Q)
			i++;
		str++;
	}
	return (i);
}

// char	ft_define_quotes_type(char *str)
// {
// 	if (ft_strchr(str, DBL_Q))
	
// }

// int	*ft_find_quotes_idx(char *str)
// {
// 	int	arr_idx;
// 	int	quotes_nb;

// 	quotes_nb = ft_count_quotes(str);
// 	if (quotes_nb == 0)
// 		return (0);

		
// 	arr_idx = (int)malloc(quotes_nb * sizeof (int));
// 	while (*str)
// 	{
		
// 	}


// 	arr_idx = (int)ft_strchr(str, DBL_Q);
		
// 	if (!arr[0])
// 		return (NULL);
// 	return (arr);
// }


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
			printf("%i\n", ft_count_quotes(current->args[i]));
			i++;
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
