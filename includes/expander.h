/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:18:15 by gdelvign          #+#    #+#             */
/*   Updated: 2024/05/16 12:10:08 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# define W_SPACE 32

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
int		ft_calculate_new_length(char *str, t_data *data);
size_t	ft_space_left(size_t buffsize, char *cursor, char *start);
void	ft_create_new_str(char *old, char *new, t_data *data, size_t buffsize);
int		ft_handle_expansion(char ***args, int idx, t_data *data);
int		ft_expand(t_data *data);

/* expander_utils.c */
int		ft_count_sgl_quotes(char *str);
int		ft_count_dbl_quotes(char *str);
int		ft_count_dollars(char *str);
int		ft_count_all_quotes(char *str);
bool	ft_is_not_valid_variable_char(char c);

/* expander_utils2.c */
char	*ft_get_env_value(char **env, char *var_name);
char	*ft_get_var_name(char *str);
void	ft_adjust_length_for_quotes(char *str, int *length);
bool	ft_should_expand_var(char *str, char *chr);

/* expander_utils3.c */
bool	ft_is_valid_var_char(char c);
void	ft_increment(int *idx, int *len);
void	ft_get_var_val_length(t_data *data, char **str, int *i, int *len);
void	ft_create_var_val(t_data *data, char **str, char **cursor,
			size_t space_left);
void	ft_process_character(char **old, char **cursor, bool state[2]);

/* expander_utils4.c */
int		ft_resplit_first_arg(char ***args);
void	ft_should_resplit(char *arg, t_data *data);

/* expander_utils5.c */
int		ft_expand_redir(t_data *data);
int		ft_expand_cmd_args(t_data *data);

#endif