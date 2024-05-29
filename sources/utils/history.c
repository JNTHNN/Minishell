/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:06:19 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:10:32 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fills the local command history with the latest input from the user.
*/
static void	ft_fill_local_history(t_data *data)
{
	t_hist	*hist;

	hist = data->hist;
	if (!hist)
		return ;
	if (hist->newline)
	{
		if (hist->lastline)
			free(hist->lastline);
		hist->lastline = ft_strdup(hist->newline);
		free(hist->newline);
	}
	hist->newline = ft_strdup(data->input);
}

/*
** Creates and initializes a new history structure.
*/
t_hist	*ft_create_hist(void)
{
	t_hist	*hist;

	hist = malloc(sizeof(t_hist));
	if (!hist)
		return (NULL);
	hist->newline = NULL;
	hist->lastline = NULL;
	return (hist);
}

/*
** Handles the command history, including saving new commands 
** and using "!!" to repeat the last command.
*/
void	ft_handle_history(t_data *data)
{
	ft_fill_local_history(data);
	add_history(data->input);
	if (ft_strlen(data->input) == 2 && !ft_strncmp(data->input, "!!", 2))
	{
		if (data->hist && data->hist->lastline)
		{
			free(data->input);
			data->input = ft_strdup(data->hist->lastline);
		}
	}
}
