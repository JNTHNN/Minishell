/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/19 17:12:24 by gdelvign         ###   ########.fr       */
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

int	ft_store_operator(char *str, int *token_nb, t_tok_lst **lst)
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
	if (!token || ft_add_tok_node(token, ++(*token_nb), OPERATOR, lst))
	{
		free(token);
		ft_throw_error(0, ERR_MEM);
	}
	return (length);
}

int	ft_store_word(char *str, int *token_nb, t_tok_lst **lst)
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
	if (!token || ft_add_tok_node(token, ++(*token_nb), WORD, lst))
	{
		free(token);
		ft_throw_error(0, ERR_MEM);
	}
	return (str - start);
}

int	ft_get_tokens(t_data *data)
{
	char	*str;
	int		token_nb;

	token_nb = 0;
	str = data->input;
	while (*str)
	{
		str += ft_skip_whitespaces(str);
		if (ft_is_operator(*str))
			str += ft_store_operator(str, &token_nb, &data->tokens);
		else
			str += ft_store_word(str, &token_nb, &data->tokens);
	}
	return (EXIT_SUCCESS);
}


t_tok_lst	*ft_tokenize(t_data *data)
{
	data->tokens = NULL;
	if (ft_check_quotes(data->input))
		ft_throw_error(0, ERR_QUOTES);
	ft_trim_input(&data->input);
	ft_get_tokens(data);

	/* print linked list nodes to check tokens only */
	t_tok_lst	*current;
	current = data->tokens;
	while (current != NULL)
	{
		printf("Le token est : \n%s\n", current->token);
		current = current->next;
	}
	/* end of printing */
	
	return (NULL);
}
