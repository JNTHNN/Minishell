/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:42:22 by gdelvign          #+#    #+#             */
/*   Updated: 2024/03/20 22:07:45 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd
{
	char				**args;
	t_tok_lst			*redirection;
	bool				is_builtin;
	struct s_cmd_node	*left;
	struct s_cmd_node	*right;
}	t_cmd;

#endif