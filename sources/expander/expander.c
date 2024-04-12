/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:15:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 21:37:31 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_calculate_new_length(char *str, t_data *data)
{
	int		i;
	int		len;
	char	*start;

	start = str;
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && ft_should_expand_var(start, &str[i]))
		{
			if (!(str[i + 1]) || ft_is_space(str[i + 1])
				|| !ft_is_valid_var_char(str[i + 1]))
				ft_increment(&i, &len);
			ft_get_var_val_length(data, &str, &i, &len);
		}
		else
			ft_increment(&i, &len);
	}
	ft_adjust_length_for_quotes(str, &len);
	return (len);
}

size_t	ft_space_left(size_t buffsize, char *cursor, char *start)
{
	return (buffsize - (cursor - start) - 1);
}

void	ft_create_new_str(char *old, char *new, t_data *data, size_t buffsize)
{
	char			*cursor;
	static bool		state[2] = {false, false};
	size_t			space_left;

	cursor = new;
	while (*old)
	{
		if (*old == DOLLAR && !state[IN_SGL_Q])
		{
			old++;
			if (!(*old) || ft_is_space(*old) || !ft_is_valid_var_char(*old))
				*cursor++ = '$';
			else
			{
				space_left = ft_space_left(buffsize, cursor, new);
				ft_create_var_val(data, &old, &cursor, space_left);
			}
		}
		else
			ft_process_character(&old, &cursor, state);
	}
	*cursor = '\0';
}

int	ft_handle_expansion(char ***args, int idx, t_data *data)
{
	char	*str;
	char	*new_str;
	char	*cursor;
	int		new_length;

	str = (*args)[idx];
	if (ft_count_all_quotes(str) || ft_count_dollars(str))
	{
		new_length = ft_calculate_new_length(str, data);
		new_str = (char *)malloc(new_length + 1);
		if (!new_str)
			return (E_MEM);
		cursor = new_str;
		ft_create_new_str(str, cursor, data, (new_length + 2));
		free((*args)[idx]);
		(*args)[idx] = new_str;
	}
	printf("FINAL = %s\n", (*args)[idx]);
	return (EXIT_SUCCESS);
}

int	ft_expand(t_data *data)
{
	t_cmd	*current;
	char	**args;
	int		i;
	int		ret;

	current = data->cmd;
	while (current)
	{
		args = current->args;
		i = 0;
		while (args[i])
		{
			ret = ft_handle_expansion(&args, i, data);
			if (ret)
				return (ret);
			i++;
		}
		current = current->right;
	}
	return (EXIT_SUCCESS);
}
