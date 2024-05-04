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

#endif