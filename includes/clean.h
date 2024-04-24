/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:32:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/16 16:30:30 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

/* clean.c */
void	ft_free_tokens(t_tok_lst **tokens);
void	ft_reset_data(t_data *data);
void	ft_free_data(t_data *data);
void	ft_free_cmds(t_cmd **cmd);
void	ft_free_if_error(t_data *data);
void	ft_free_exec(t_data *data);

#endif