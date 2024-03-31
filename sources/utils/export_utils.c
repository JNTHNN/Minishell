/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:26:19 by jgasparo          #+#    #+#             */
/*   Updated: 2024/03/31 01:18:50 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Initialize env in linked list
*/

static void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (!lst)
		return ;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;
}

static void	ft_add_env(t_env **head, char *var)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->var = var;
	new_node->next = NULL;
	ft_envadd_back(head, new_node);
}

char	*ft_strndup(char *s1, int size)
{
	int	i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
static char	*ft_var(char *s)
{
	char *equal_sign;
	int	size;
	char	*var;
	
	var = NULL;
	equal_sign = ft_strchr(s, '=');
	if (equal_sign)
	{
		size = equal_sign - s + 1;
		var = ft_strndup(s, size);
	}
	return (var);
}

// static char	*ft_data(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s && s[i])
// 	{
// 		if (s[i] == '=')
// 			return (&s[i + 1]);
// 		i++;
// 	}
// 	return (s);
// }

static char	*ft_data(char *s)
{
	char *equal_sign;
	char *data;
	int	start;

	data = NULL;
	equal_sign = ft_strrchr(s, '=');
	if (equal_sign)
	{
		start = equal_sign - s + 1;
		data = ft_strdup(s + start);
	}
	return (data);
}

static t_env	*ft_new_node(char *var)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (node)
	{
		node->var = ft_var(var);
		node->data = ft_data(var);
		node->next = NULL;
	}
	return (node);
}


t_env	*ft_setup_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*node;

	head = NULL;
	current = NULL;
	if (!env || !*env)
		return (NULL);
	while (*env)
	{
		node = ft_new_node(*env);
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
	return (head);
}

/*
**	Check if var env already exist then modify
**	or just add
*/



void	ft_modify_or_add_env(t_env **head, char *var)
{
	t_env	*current;
	char	*equal_sign;
	char	*deb;
	char	*fin;
	char	*zeub;
	
	deb = ft_var(var);
	fin = ft_data(var);
	zeub = ft_strtrim(fin, "\"");
	
	printf("TEST DEB[%s]\n", deb);
	printf("TEST FIN[%s]\n", fin);
	printf("TEST ZEUB[%s]\n", zeub);

	current = *head;
	printf("TEST VAR[%s]\n", var);
	equal_sign = ft_strchr(var, '=');
	printf("TEST DATA[%s]\n", equal_sign);
	if (equal_sign)
	{
		// *equal_sign = '\0';
		printf("TEST 2 VAR[%s]\n", var);
		printf("TEST 2 DATA[%c]\n", *equal_sign);
		while (current)
		{
			if (!ft_strncmp(current->var, var, ft_strlen(var)))
			{
				free(current->var);
				current->var = ft_strdup(var);
				*equal_sign = '=';
				return ;
			}
			current = current->next;
		}
		*equal_sign = '=';
	}
	ft_add_env(head, var);
}
