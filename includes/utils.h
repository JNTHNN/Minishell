/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:49:29 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/29 11:38:50 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* utils.c */
void	*ft_free_array(char **arr);
char	**ft_create_env(char **arr);
char	**ft_envcpy(char **arr);

/*	utils2.c	*/
int		ft_tablen(char **str);
char	**ft_add_to_env(char **env, char *new_var);
char	*ft_getenv(t_data *data, char *search);

#endif