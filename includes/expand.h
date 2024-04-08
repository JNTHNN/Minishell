/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:18:15 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/08 22:25:17 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

enum e_state
{
	IN_DBL_Q = 0,
	IN_SGL_Q = 1
};

enum e_var
{
	NAME = 0,
	VAL = 1
};

int	ft_expand(t_data *data);

#endif