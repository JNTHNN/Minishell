/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:06:19 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/09 14:44:32 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_fill_local_history(t_data *data)
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
