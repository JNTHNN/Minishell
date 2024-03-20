/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:42:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/20 10:24:21 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd_node
{
	char				**args;
	t_tok_lst			*redirection;
	struct s_cmd_node	*left;
	struct s_cmd_node	*right;
}	t_cmd_node;

#endif