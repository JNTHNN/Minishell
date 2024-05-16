/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:32:04 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 11:50:16 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

/*		clean.c		*/
void	ft_free_tokens(t_tok_lst **tokens);
void	ft_free_cmds(t_cmd **cmd);
void	ft_free_data(t_data *data);

/*		clean2.c	*/
void	ft_free_if_error(t_data *data);
void	ft_free_exec(t_data *data);
void	ft_reset_data(t_data *data);

#endif