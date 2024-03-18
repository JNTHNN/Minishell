/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:05 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/18 16:20:33 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_quote(char c)
{
	if (c == DBL_Q || c == SGL_Q)
		return (true);
	return (false);
}

static bool	ft_is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

static bool	ft_is_operator(char c)
{
	if (c == REDIR_IN || c == REDIR_OUT || c == PIPE_OP)
		return (true);
	return (false);
}

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

/* TODO: refacto this function) */
int	ft_count_tokens(char *input)
{
	int		count;
	int		quote_char;
	bool	in_quotes;
	char	*start;

	start = input;
	count = 0;
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
				if (input == start
					|| (input > start && ft_is_space(*(input - 1))))
					count++;
			}
			else if (*input == quote_char)
				in_quotes = false;
			input++;
			continue ;
		}
		if (!in_quotes && ft_is_operator(*input))
		{
			count++;
			while (*input && ft_is_operator(*(input)))
				input++;
		}
		else if (!in_quotes && !ft_is_space(*input))
		{
			count++;
			while (*input && !ft_is_space(*input) && !ft_is_quote(*input)
				&& !ft_is_operator(*input))
				input++;
		}
		else if (ft_is_space(*input))
			input++;
		if (in_quotes)
		{
			while (*input && (*input != quote_char))
				input++;
			if (*input == quote_char)
			{
				in_quotes = false;
				input++;
			}
		}
	}
	return (count);
}

// void	ft_get_tokens(t_data *data)
// {
// 	int			count;
// 	int			quote_char;
// 	bool		in_quotes;
// 	char 		*begin;
// 	char		*start;
// 	char		*end;
// 	char 		*str;

// 	str = data->input;
// 	begin = str;
// 	quote_char = 0;
// 	count = 0;
// 	in_quotes = false;
// 	while (*str)
// 	{
// 		if (ft_is_quote(*str))
// 		{
// 			if (!in_quotes)
// 			{
// 				in_quotes = true;
// 				start = str;
// 				quote_char = *str;
// 				//str++;
// 				if (str == begin
// 					|| (str > begin && ft_is_space(*(str - 1))))
// 				{
// 					count++;
// 					while (*str && *str != quote_char)
// 						str++;
// 					end = str + 1;
// 					if (*str)
// 						str++;
// 					printf("|%s|\n", ft_substr(data->input, start - data->input, end - start));
// 					//ft_add_tok_node(ft_substr(data->input, start - data->input, end - start), count, LITTERAL, &data->tokens);
// 				}
// 			}
// 			else if (*str == quote_char)
// 				in_quotes = false;
// 			str++;
// 			continue ;
// 		}
// 		if (!in_quotes && ft_is_operator(*str))
// 		{
// 			count++;
// 			while (*str && ft_is_operator(*(str)))
// 				str++;
// 		}
// 		else
// 			str++;
// 	}
// 	printf("%i", count);
// }

void	ft_get_tokens(t_data *data)
{
	char	*str;
	char	*start;
	int		quote_char;
	bool	in_quotes;
	int		token_id;
	char	*previous;

	str = data->input;
	in_quotes = false;
	token_id = 0;
	previous = NULL;
	while (*str)
	{
		if (ft_is_quote(*str))
		{
			in_quotes = !in_quotes;
			start = str;
			quote_char = *str;
			str++;
			while (*str && *str != quote_char)
				str++;
			if (in_quotes || (!in_quotes && (previous == NULL || (previous && ft_is_space(*previous)))))
			{
				if (*str)
					str++;
				ft_add_tok_node(ft_substr(data->input, start - data->input, str - start), token_id++, WORD, &data->tokens);
			}
		}
		else if (!in_quotes && (ft_is_operator(*str) || !ft_is_space(*str)))
		{
			start = str;
			if (ft_is_operator(*str))
			{
				while (*str && ft_is_operator(*str))
					str++;
				ft_add_tok_node(ft_substr(data->input, start - data->input, str - start), token_id++, OPERATOR, &data->tokens);
			}
			else
			{
				while (*str && !ft_is_space(*str) && !ft_is_quote(*str) && !ft_is_operator(*str))
					str++;
				ft_add_tok_node(ft_substr(data->input, start - data->input, str - start), token_id++, WORD, &data->tokens);
			}
		}
		else
		{
			previous = str;
			str++;
		}
	}
}


t_tok_lst	*ft_tokenize(t_data *data)
{
	int				tok_nb;

	data->tokens = NULL;
	if (ft_check_quotes(data->input))
		ft_throw_error(0, ERR_QUOTES);
	tok_nb = ft_count_tokens(data->input);
	ft_get_tokens(data);

	t_tok_lst	*current;
	current = data->tokens;
	while (current != NULL)
	{
		printf("Le token est : \n%s\n", current->token);
		current = current->next;
	}
	printf("nb of tokens = %i\n", tok_nb);

	return (NULL);
}
