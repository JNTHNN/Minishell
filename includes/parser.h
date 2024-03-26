/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:42:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:51 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		ft_parse(t_data *data);
t_cmd	*ft_create_new_cmd(char ***args);
int		ft_add_cmd_node(char ***args, t_data *data);
int		ft_add_redir_node(t_redir_lst *lst, t_tok_lst *token, int cmd_nb);

#endif