/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:18:15 by gdelvign          #+#    #+#             */
/*   Updated: 2024/04/12 16:47:11 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

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

/* expander.c */
int		ft_expand(t_data *data);

/* expander_utils.c */
int		ft_count_sgl_quotes(char *str);
int		ft_count_dbl_quotes(char *str);
int		ft_count_dollars(char *str);
int		ft_count_all_quotes(char *str);

/* expander_utils2.c */
char	*ft_get_env_value(char **env, char *var_name);
char	*ft_get_var_name(char *str);
void	ft_adjust_length_for_quotes(char *str, int *length);
bool	ft_should_expand_var(char *str, char *chr);

/* expander_utils3.c */
bool	ft_is_not_valid_variable_char(char c);
bool	ft_is_valid_var_char(char c);
void	ft_increment(int *idx, int *len);
void	ft_get_var_val_length(t_data *data, char **str, int *i, int *len);

#endif