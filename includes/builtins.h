/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:30:39 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/04 10:30:40 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define OLDPWD "OLDPWD="
# define HOME "HOME="
# define PWD "PWD="
# define TILDE "~"
# define MINUS "-"
# define PARENT ".."
# define CURRENT "."
# define TPLUS "~+"
# define TMINUS "~-"

/* Handle all builtins : builtins.c	*/
bool	ft_is_builtin(char *name);
int		ft_builtin(t_data *data, t_cmd *cmd);

void	ft_echo(t_data *data, t_cmd *cmd);
void	ft_cd(t_data *data, t_cmd *cmd);
void	ft_pwd(t_data *data);
int		ft_export(t_data *data, t_cmd *cmd);
void	ft_env(t_data *data);
int		ft_exit(t_data *data, t_cmd *cmd);
void	ft_unset(t_data *data, t_cmd *cmd);

/*  utils for cd : cd_utils.c   */
void	ft_seek_replace(t_data *data, char *search, char *pwd);
void	ft_cd_home(t_cd *cd);
void	ft_cd_absolute(t_cd *cd);
void	ft_cd_relative(t_cd *cd);

/*  manipulate tab for cd : cd_utils2.c */
char	**ft_append_pwd(char **pwd, char *path);
char	**ft_sup_pwd(char **pwd);
char	*ft_pwdcat(char **pwd);
char	**ft_remove_first(char **path);
char	**ft_replace_pwd(t_cd *cd, char *shortcut);

/*	checker for cd : cd_utils3.c	*/
int		ft_check_tilde(t_cd *cd);
int		ft_check_home(t_cd *cd);
int		ft_check_minus(t_cd *cd);

/*  utils for export : export_utils.c   */
t_env	*ft_setup_env(char **env);
void	ft_modify_or_add_env(t_env **head, char *var);

/* prints for export : export_utils2.c  */
void	ft_print_env(t_env *head);

/* update_env for export : export_utils3.c    */
void	ft_update_env(t_env *head, t_data *data);

/*  var + data for export : export_utils4.c */
char	*ft_var(char *s);
char	*ft_data(char *s);

#endif