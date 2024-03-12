/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JG_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/02/29 20:53:25 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	export sans aucune option a l'execution va print "declare -x" par variable
**	de l'env triée par ordre ascii ? 
**	export avec un nom de variable va l'ajouter aux variables d'env sans print
**	The export and declare -x commands allow parameters and functions to be 
**	added to and deleted from the environment.
**	export test1 : test1 n'est pas herite dans l'env mais visible avec export seul
**	export test1= : test1 est herite dans l'env avec la valeur qui suit = / donc 
**	visible dans env.
**	declare -x rajoute des "" pour le contenu de la variable
*/

#include "../../includes/minishell.h"

t_env *new_node(char *var)
{
    t_env	*node;
	
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
    if (node)
    {
        node->var = ft_strdup(var);
        node->next = NULL;
    }
    return node;
}

t_env *setup_env(char **env)
{
    t_env	*head;
    t_env	*current;

	head = NULL;
	current = NULL;
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
    char	*temp;
	
	temp = a->var;
    a->var = b->var;
    b->var = temp;
}

void sort_env(t_env *head)
{
    int		swapped;
    t_env	*unsort;
    t_env	*sorted;

	swapped = 1;
	sorted = NULL;
    if (head == NULL)
        return;

    while (swapped)
    {
        swapped = 0;
        unsort = head;

        while (unsort->next != sorted)
        {
            if (ft_strncmp(unsort->var, unsort->next->var, ft_strlen(unsort->var)) > 0)
            {
                swap_nodes(unsort, unsort->next);
                swapped = 1;
            }
            unsort = unsort->next;
        }
        sorted = unsort;
    }
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (!lst)
		return ;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;
}

void add_env(t_env **head, char *var)
{
    t_env	*new_node;
	
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->var = var;
	new_node->next = NULL;
	ft_envadd_back(head, new_node);
}

void modify_or_add_env(t_env **head, char *var)
{
    t_env *current;
    char *equal_sign;

	current = *head;
    equal_sign = ft_strchr(var, '=');
    if (equal_sign)
    {
        *equal_sign = '\0'; // Temporarily terminate the string here
        while (current)
        {
            if (!ft_strncmp(current->var, var, ft_strlen(var))) // The variable exists, modify its value
            {
                free(current->var); // Free the old variable
                current->var = ft_strdup(var); // Duplicate the new variable
                *equal_sign = '='; // Restore the original character
                return;
            }
            current = current->next;
        }
        *equal_sign = '='; // Restore the original character
    }
    add_env(head, var); // The variable does not exist, add it
}

void print_env(t_env *head)
{
	char *equal_sign;

    sort_env(head);
    while (head)
    {
        equal_sign = ft_strchr(head->var, '=');
        if (equal_sign)
		{
            *equal_sign = '\0'; // Temporarily terminate the string here
            printf("declare -x %s=\"%s\"\n", head->var, equal_sign + 1);
            *equal_sign = '='; // Restore the original character
        }
		else
            printf("declare -x %s\n", head->var);
        head = head->next;
    }
}
void show_list(t_env *head)
{
    while (head)
    {
        printf("%s\n", head->var);
        head = head->next;
    }
}

void	export_builtin(char **cmd, char **env)
{
	t_env *head;

	head = setup_env(env);
	if (!ft_strncmp(cmd[0], "export", 6))
	{
		if (cmd[1])
		{
			printf("test : %s\n", cmd[1]);
			modify_or_add_env(&head, cmd[1]); // ajouter ou modifie la variable a la liste chainee
			show_list(head); // print la liste chainee
		}
		else
		{
			 print_env(head);// print la liste chainee
		}
	}
}


/*	Faire une liste chainee du nouvel env -> ajouter a la suite 
**	export test -> rajoute test dans la declare -x test mais pas dans env
**	Ensuite export va print dans l'ordre ascii mais ne la range pas dans l'ordre ascii
**	si test="" -> export pareil mais la rajoute dans l'env dnas l'ordre ascii

export

    export [-fn] [-p] [name[=value]]

    Mark each name to be passed to child processes in the environment. If the -f option is supplied, the names refer to shell functions;
	otherwise the names refer to shell variables. The -n option means to no longer mark each name for export. 
	If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed.
	The -p option displays output in a form that may be reused as input. If a variable name is followed by =value, the value of the variable is set to value.
    The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a shell function.
*/