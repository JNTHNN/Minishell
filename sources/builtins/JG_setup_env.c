/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JG_setup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:36:32 by jgasparo          #+#    #+#             */
/*   Updated: 2024/02/01 11:10:16 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	TO DO	
**	Recevoir l'env de base et creer une liste chainee 
**	Chaque node correspond a une variable
**	Possibilite de supprimer / modifier / ajouter variable
**	avoir un check qui va trier / afficher chaque node dans un ordre ascii
*/

#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
    char *var;
    struct s_env *next;
} t_env;

t_env *new_node(char *var)
{
    t_env *node = malloc(sizeof(t_env));
    if (node)
    {
        node->var = strdup(var);
        node->next = NULL;
    }
    return node;
}

t_env *setup_env(char **env)
{
    t_env *head = NULL;
    t_env *current = NULL;

    if (!env || !*env)
        return NULL;

    while (*env)
    {
        t_env *node = new_node(*env);
        if (!head)
        {
            head = node;
            current = node;
        }
        else
        {
            current->next = node;
            current = node;
        }
        env++;
    }

    return head;
}

void swap_nodes(t_env *a, t_env *b)
{
    char *temp = a->var;
    a->var = b->var;
    b->var = temp;
}

void sort_env(t_env *head)
{
    int swapped;
    t_env *ptr1;
    t_env *lptr = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->var, ptr1->next->var) > 0)
            {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void print_env(t_env *head)
{
    sort_env(head);
    while (head)
    {
        printf("%s\n", head->var);
        head = head->next;
    }
}