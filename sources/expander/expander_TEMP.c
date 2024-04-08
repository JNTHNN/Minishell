/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_TEMP.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/04 12:48:05 by gdelvign         ###   ########.fr       */
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

int	ft_handle_expansion(char ***args, int idx, char **env)
{
	char	*str;
	int		nb_of_q;
	int		str_size;
	int		nb_of_doll;
	int		i;
	int		j;
	bool	keep_sgl_q;
	bool	keep_dbl_q;
	char	*single_q;
	char	*double_q;
	char	*dollar;
	char	*prev_dollar;
	char 	next_char;
	char 	*new_str;
	bool 	in_sgl_q;
	bool 	in_dbl_q;
	char 	*temp;
	char 	*start;
	char	*var;
	
	str = (*args)[idx];
	nb_of_q = ft_count_sgl_quotes(str) + ft_count_dbl_quotes(str);
	str_size = (int)ft_strlen(str);
	nb_of_doll = ft_count_dollars(str);
	keep_sgl_q = false;
	keep_dbl_q = false;
	printf("NB OF QUOTES = %d \n", nb_of_q);
	printf("NB OF DOLLARS = %d \n", nb_of_doll);
	printf("STR SIZE = %d \n", str_size);
	if (nb_of_q && !nb_of_doll)
	{
		single_q = ft_strchr(str, SGL_Q);
		double_q = ft_strchr(str, DBL_Q);
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
		printf("ARG : %s\n", (*args)[idx]);
	}
	if (nb_of_doll)
	{
		i = 0;
		dollar = str;
		prev_dollar = str;
		while (true)
		{
			dollar = ft_strchr(dollar, DOLLAR);
			if (dollar == NULL)
				break;
			printf("%s\n", dollar);	
			if (nb_of_q)
			{
				in_sgl_q = false;
				in_dbl_q = false;
				temp = prev_dollar;
				while (temp < dollar)
				{
					if (*temp == SGL_Q && !in_dbl_q)
						in_sgl_q = !in_sgl_q;
					else if (*temp == DBL_Q && !in_sgl_q)
						in_dbl_q = !in_dbl_q;
					temp++;
				}
			}
			next_char = *(dollar + 1);
			if (next_char == '\0' || ft_is_space(next_char))
			{
				dollar++;
				continue;
			}
			if (!ft_is_valid_variable_char(next_char))
			{
				free((*args)[idx]);
				(*args)[idx] = ft_strdup("\0");
				dollar++;
				continue;
			}
			dollar++;
			start = dollar;
			while (*dollar && (!ft_is_space(*dollar) && !ft_is_quote(*dollar) && *dollar != DOLLAR))
					dollar++;
			var = ft_substr(start, 0, dollar - start);
			temp = ft_strjoin(var, "=");
			free(var);
			var = NULL;
			printf("%s\n", temp);
			if (!in_sgl_q && env)
			{
				j = 0;
				while (env[j])
				{
					if (!ft_strncmp(env[j], temp, ft_strlen(temp)))
					{
						var = ft_substr(env[j], ft_strlen(temp), ft_strlen(env[j]) - ft_strlen(temp));
						if (!var)
							return (E_MEM);
						free((*args)[idx]);
						(*args)[idx] = var;
					}
					j++;
				}
				//printf("%s\n", var);
			}
			if (!var)
			{
				free((*args)[idx]);
				(*args)[idx] = ft_strdup("\0");
			}
			printf("ARG : %s\n", (*args)[idx]);
			i++;
		}
	}
	printf("=================================================================================================================\n");
	return (EXIT_SUCCESS);
}
