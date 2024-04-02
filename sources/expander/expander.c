/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/02 12:19:45 by gdelvign         ###   ########.fr       */
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

int	ft_count_dollars(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == DOLLAR)
			i++;
		str++;
	}
	return (i);
}

// bool	ft_dollar_in_sgl_q(char *str)
// {
// 	int		i;
// 	char	*dollar;

// 	dollar = ft_strchr(str, DOLLAR);
	
// 	while (str[i])
// 	{
// 		if () 
// 	}
// }


// char	ft_define_quotes_type(char *str)
// {
// 	if (ft_strchr(str, DBL_Q))
	
// }

// int	ft_find_quotes_idx(char *str, t_cmd **cmd, int id)
// {
// 	t_expand	*arr_idx;
// 	int			exp_char_nb;
// 	int			i;
// 	char		*start;

// 	start = str;
// 	exp_char_nb = ft_count_expand_char(str);
// 	if (exp_char_nb == 0)
// 		return (0);
// 	arr_idx = (t_expand *)malloc((exp_char_nb + 1) * sizeof(t_expand));
// 	if (!arr_idx)
// 		return (E_MEM);
// 	i = -1;
// 	while (++i < exp_char_nb)
// 		arr_idx[i].id = -1;
// 	arr_idx[exp_char_nb].id = -1;
// 	i = 0;
// 	while (*str)
// 	{
// 		if (ft_is_expand_char(*str))
// 		{
// 			if (*str == DBL_Q)
// 				arr_idx[i].char_type = DBL_Q;
// 			else if (*str == SGL_Q)
// 				arr_idx[i].char_type = SGL_Q;
// 			else if (*str == DOLLAR)
// 				arr_idx[i].char_type = DOLLAR;
// 			arr_idx[i].position = str - start;
// 			arr_idx[i].id = i;
// 			i++;
// 		}
// 		str++;
// 	}
// 	if (arr_idx[0].id == -1)
// 		return (-1);
// 	(*cmd)->expanded_char[id] = arr_idx;
// 	return (EXIT_SUCCESS);
// }


int	ft_handle_expansion(char ***args, int idx, char **env)
{
	char	*str;
	int		nb_to_del;
	int		str_size;
	int		nb_of_doll;
	int		i;
	int		j;
	char	*var;
	bool	is_single;

	str = (*args)[idx];
	nb_to_del = ft_count_quotes(str);
	str_size = (int)ft_strlen(str);
	nb_of_doll = ft_count_dollars(str);
	is_single = false;
	printf("NB OF QUOTES = %d \n", nb_to_del);
	printf("NB OF DOLLARS = %d \n", nb_of_doll);
	printf("STR SIZE = %d \n", str_size);
	if (nb_of_doll)
	{
		i = 0;
		char	*dollar = str;
		while (i < nb_of_doll)
		{
			dollar = ft_strchr(dollar, DOLLAR);
			if (ft_strchr(dollar, SGL_Q))
				is_single = true;
			if ((dollar + 1))
				dollar++;
			char *start = dollar;
			while(*dollar && (!ft_is_space(*dollar) && !ft_is_quote(*dollar)))
					dollar++;
			var = ft_substr(start, 0, dollar - start);
			printf("IS_SINGLE = %d\n", is_single);
			printf("%s\n", var);
			if (!is_single && env)
			{
				j = 0;
				while (env[j])
				{
					j++;
				}
				printf("ENV : %s\n", env[0]);
			}

			
			free(var);
			i++;
		}
	}
	
	return (EXIT_SUCCESS);
}


int	ft_expand(t_data *data)
{
	t_cmd	*current;
	char 	**args;
	int		i;

	current = data->cmd;
	while (current)
	{
		args = current->args;
		i = 0;
		while (args[i])
		{
			ft_handle_expansion(&args, i, data->env);
			i++;
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}




// int	ft_expand(t_data *data)
// {
// 	t_cmd	*current;
// 	int		i;
// 	int		arg_size;

// 	current = data->cmd;
// 	while (current)
// 	{
// 		arg_size = 0;
// 		while (current->args[arg_size])
// 			arg_size++;
// 		current->expanded_char = (t_expand **)malloc(arg_size * sizeof(t_expand *));
// 		if (!current->expanded_char)
// 			return (E_MEM);
// 		i = -1;
// 		while (++i < arg_size)
// 			current->expanded_char[i] = NULL;
// 		i = 0;
// 		while (current->args[i])
// 		{
// 			ft_find_quotes_idx(current->args[i], &current, i);
// 			i++;
// 		}
// 		current = current->right;
// 	}

// 		// PRINT RESULTS FOR TESTING
// 	current = data->cmd;
// 	while (current)
// 	{
// 		printf("CMD %i\n", current->id);
// 		arg_size = 0;
// 		while (current->args[arg_size])
// 			arg_size++;
// 		i = 0;
// 		while (i < arg_size)
// 		{
// 			if (current->expanded_char[i] != NULL)
// 			{
// 				int j = 0;
// 				while (current->expanded_char[i][j].id != -1)
// 				{
// 					printf("Arg %d, expand char %d, position: %d and char_type %c\n", i, j, current->expanded_char[i][j].position, current->expanded_char[i][j].char_type);
// 					if (current->expanded_char[i][j].char_type == DOLLAR && (current->expanded_char[i][j - 1].id != -1 && current->expanded_char[i][j - 1].char_type == DBL_Q))
// 						printf("DOLLAR is in DLB QUOTES\n");
// 					j++;
// 				}
// 			}
// 			i++;
// 		}
// 		current = current->right;
// 	}
// 	// END OF PRINTING
	
// 	return (EXIT_SUCCESS);
// }
