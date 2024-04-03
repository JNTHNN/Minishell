/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/03 17:31:10 by gdelvign         ###   ########.fr       */
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

int	ft_count_sgl_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == SGL_Q)
			i++;
		str++;
	}
	return (i);
}

int	ft_count_dbl_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == DBL_Q)
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

bool	ft_is_valid_variable_char(char c)
{
	if (ft_isalpha(c) || c == UNDERSCORE)
		return (true);
	return (false);
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

/* TODO: code a function to check if token has  simple quotes around (before double) */

// bool ft_sould_expand_dollar(char *d_str)
// {
// 	char	*single_q;
// 	char	*double_q;
// 	char 	*next_doll;
	
// 	single_q = ft_strchr(d_str, SGL_Q);
// 	double_q = ft_strchr(d_str, DBL_Q);
// 	next_doll = ft_strchr(d_str, DOLLAR);

// 	if (!single_q && !double_q)
// 		return (true);
// 	while (*d_str)
// 	{
		
// 	}
	
// 	return (false);
// }


int	ft_handle_expansion(char ***args, int idx, char **env)
{
	char	*str;
	int		nb_of_q;
	int		str_size;
	int		nb_of_doll;
	int		i;
	int		j;
	bool	is_single;
	bool	keep_sgl_q;
	bool	keep_dbl_q;
	bool	expand_dol;
	char	*single_q;
	char	*double_q;
	char 	next_char;
	char 	*new_str;
	int		doll_idx;
	char 	*start;
	char	*var;

	(void)env;
	str = (*args)[idx];
	nb_of_q = ft_count_sgl_quotes(str) + ft_count_dbl_quotes(str);
	str_size = (int)ft_strlen(str);
	nb_of_doll = ft_count_dollars(str);
	is_single = false;
	keep_sgl_q = false;
	keep_dbl_q = false;
	expand_dol = false;
	printf("NB OF QUOTES = %d \n", nb_of_q);
	printf("NB OF DOLLARS = %d \n", nb_of_doll);
	printf("STR SIZE = %d \n", str_size);
	if (nb_of_q && !nb_of_doll)
	{
		single_q = ft_strchr(str, SGL_Q);
		double_q = ft_strchr(str, DBL_Q);
		if (single_q && !double_q)
			is_single = true;
		if ((single_q && double_q) && (double_q - single_q > 0))
			keep_dbl_q = true;
		if ((single_q && double_q) && (single_q - double_q > 0))
			keep_sgl_q = true;
		if (double_q && !keep_dbl_q)
			str_size -= ft_count_dbl_quotes(str);
		if (single_q && !keep_sgl_q)
			str_size -= ft_count_sgl_quotes(str);	
		new_str = (char *)malloc((str_size + 1) * sizeof(char));
		if (!new_str)
			return (E_MEM);
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] == DBL_Q && !keep_dbl_q)
				i++;
			else if (str[i] == SGL_Q && !keep_sgl_q)
				i++;
			else
			{
				new_str[j] = str[i];
				j++;
				i++;
			}
		}
		new_str[j] = '\0';
		free((*args)[idx]);
		(*args)[idx] = new_str;
	}
	if (nb_of_doll)
	{


		
		i = 0;
		char	*dollar = str;
		while (true)
		{
			dollar = ft_strchr(dollar, DOLLAR);
			if (dollar == NULL)
				break;
			start = str;
			doll_idx = dollar - start;
			printf("DOLLAR INDEX = %d\n", doll_idx);
			printf("%s\n", dollar);	
			if (nb_of_q)
			{
				//
			}
			
			next_char = *(dollar + 1);
			if (next_char == '\0' || ft_is_space(next_char) || !ft_is_valid_variable_char(next_char))
			{
				dollar++;
				continue;
			}
			dollar++;
			
			//if (single_q || ((single_q && double_q) && (double_q - single_q > 0)));

			start = dollar;
			while(*dollar && (!ft_is_space(*dollar) && !ft_is_quote(*dollar) && *dollar != DOLLAR))
					dollar++;
			var = ft_substr(start, 0, dollar - start);
			printf("IS_SINGLE = %d, KEEP_SGL = %d, KEEP_DBL = %d, EXPAND_DOL = %d\n", is_single, keep_sgl_q, keep_dbl_q, expand_dol);
			printf("%s\n", var);
			if (!is_single && env)
			{
				j = 0;
				while (env[j])
				{
					j++;
				}
				//printf("ENV : %s\n", env[0]);
			}

			
			free(var);
			i++;
		}
	}
	printf("=================================================================================================================\n");
	return (EXIT_SUCCESS);
}


int	ft_expand(t_data *data)
{
	t_cmd	*current;
	char 	**args;
	int		i;
	int		ret;

	current = data->cmd;
	while (current)
	{
		args = current->args;
		i = 0;
		while (args[i])
		{
			ret = ft_handle_expansion(&args, i, data->env);
			if (ret)
				return (ret);
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
