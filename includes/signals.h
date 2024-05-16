/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:19:33 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/16 12:21:12 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Handle signals : signals.c	*/
void	ft_sigint(int sig);
void	ft_signal(void *type);
void	ft_get_ctrl_d(t_data *data);
int		ft_init_signal(void);
void	rl_replace_line(const char *text, int clear_undo);

#endif