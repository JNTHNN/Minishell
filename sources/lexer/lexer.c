/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/25 11:45:51 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_quotes(char *input)
{
	int		quote_char;
	bool	in_quotes;

	quote_char = 0;
	in_quotes = false;
	while (*input)
	{
		if (ft_is_quote(*input))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_char = *input;
			}
			else if (*input == quote_char)
				in_quotes = false;
		}
		input++;
	}
	if (in_quotes)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_store_operator(t_data *data, char *str, int *token_nb)
{
	char	*token;
	int		length;

	length = 0;
	if ((*str == REDIR_IN && *(str + 1) == REDIR_IN)
		|| (*str == REDIR_OUT && *(str + 1) == REDIR_OUT))
		length = 2;
	else
		length = 1;
	token = ft_substr(str, 0, length);
	if (!token || ft_add_tok_node(token, ++(*token_nb), OPERATOR, data))
	{
		free(token);
		return (E_MEM);
	}
	return (length);
}

int	ft_store_word(t_data *data, char *str, int *token_nb)
{
	char	quote_char;
	char	*start;
	char	*token;

	start = str;
	quote_char = 0;
	while (*str && !ft_is_operator(*str))
	{
		ft_handle_quoted_word(&str, &quote_char);
		if (ft_is_space(*str))
			break ;
	}
	token = ft_substr(start, 0, str - start);
	if (!token || ft_add_tok_node(token, ++(*token_nb), WORD, data))
	{
		free(token);
		return (E_MEM);
	}
	return (str - start);
}

int	ft_get_tokens(t_data *data)
{
	char	*str;
	int		token_nb;
	int		ret;

	token_nb = 0;
	str = data->input;
	while (*str)
	{
		str += ft_skip_whitespaces(str);
		if (ft_is_operator(*str))
		{
			ret = ft_store_operator(data, str, &token_nb);
			if (ret < 0)
				return (ret);
			str += ret;
		}
		else
		{
			ret = ft_store_word(data, str, &token_nb);
			if (ret < 0)
				return (ret);
			str += ret;
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_tokenize(t_data *data)
{
	data->tokens = NULL;
	if (ft_check_quotes(data->input))
		return (E_QUOTES);
	if (ft_trim_input(&data->input))
		return (E_MEM);
	if (ft_get_tokens(data))
		return (E_MEM);
	if (ft_check_pipes(data->tokens))
		return (E_PIPE);

	/* print token linked list nodes to check results while coding */
	// t_tok_lst	*current;
	// current = data->tokens;
	// while (current != NULL)
	// {
	// 	printf("Token %i = %s\n", current->id, current->token);
	// 	current = current->next;
	// }
	/* end of printing results */
	
	return (EXIT_SUCCESS);
}
