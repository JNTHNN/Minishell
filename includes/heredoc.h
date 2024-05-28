/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:07:09 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/28 17:12:23 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

/* heredoc.c */
int		ft_trigger_heredoc(t_data *data);

/* hredoc_utils.c */
void	ft_create_new_line(char *old, char *new,
			t_data *data, size_t buffsize);
int		ft_calc_line_new_len(char *str, t_data *data);

#endif