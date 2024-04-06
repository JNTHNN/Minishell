/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:49:29 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/06 22:47:13 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* utils.c */
char	**ft_arrcpy(char **arr);
void	*free_arr(char **arr);
char	**ft_envcpy(char **arr);
char	**ft_create_env(char **arr);

/*	utils2.c	*/
char	*ft_getenv(t_data *data, char *search);
char	**ft_add_to_env(char **env, char *new_var);
int		ft_tablen(char **str);
void	ft_free_array(char **env);

#endif