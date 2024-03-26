/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:30:58 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/19 15:57:36 by gdelvign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	unset sans rien ? ne se passe rien mais ne doit pas etre considerer comme une erreur
**	unset avec un nom de variable presente dans l'env va la supprimer. peut unset plusieurs var a la fois
*/

#include <stdlib.h>

void ft_my_unset(char **args, char ***envp) 
{
    int i = 0;
    
    while (args[i]) 
    {
        int j = 0;
        while ((*envp)[j]) 
        {
            if (ft_strncmp(args[i], (*envp)[j], ft_strlen(args[i])) == 0) 
            {
                free((*envp)[j]);
                while ((*envp)[j]) 
                {
                    (*envp)[j] = (*envp)[j + 1];
                    j++;
                }
                break;
            }
            j++;
        }
        i++;
    }
}