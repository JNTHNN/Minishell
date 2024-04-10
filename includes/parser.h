/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:42:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/28 12:11:05 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* parser.c */
int		ft_parse(t_data *data);

/* parser_utils.c */
t_cmd	*ft_create_new_cmd(char ***args, t_data *data, int id);
int		ft_add_cmd_node(char ***args, t_data *data, int id);

/* parser_utils2.c */
int		ft_add_redir_node(t_redir_lst **lst, t_tok_lst *token, int cmd_nb);

/* parser_utils3.c */
int		ft_count_pipes(t_tok_lst *lst);
void	ft_nullify_tok_nodes(t_tok_lst *node);
void	ft_remove_redir(t_tok_lst *lst);
int		ft_init_redir(t_redir_lst ***redirections, t_data **data, int *cmd_nb);
int		ft_count_cmd_args(t_tok_lst **current);

#endif