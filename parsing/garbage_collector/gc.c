/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:17:53 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/08 19:11:35 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_garbage *get_last_node(t_garbage *list)
{
    while(list->next)
    {
        list = list->next;
    }
    return(list);
}

void add_node(t_garbage **list, t_garbage *new)
{
    if(!list || !(*list))
    {
        *list = new;
        return;
    }
    new->next = *list;
    *list = new;
    return;
}


void *gc_malloc(size_t size, t_garbage **list)
{
    void *ptr;
    t_garbage *new;
    ptr = malloc(size);
    if (!ptr)
        return(NULL);
    new = malloc(sizeof(t_garbage));
    if (!new)
    {
        free(ptr);
        return(NULL);
    }
    new->next = NULL;
    new->adress = ptr;
    add_node(list, new);
    return(ptr);
}

t_garbage **getter()
{
    static t_garbage *gc;
    return(&gc);
}

void free_all(t_garbage **list)
{
    t_garbage *next;
    while((*list))
    {
        free((*list)->adress);
        next = (*list)->next;
        free((*list));
        (*list) = next;
    }
    *list = NULL;
}

t_garbage *get_adress(void *adress, t_garbage *list)
{
    while(list)
    {
        if(list->adress == adress)
            return(list);
        list = list->next;
    }
    return(list);
}

char	*gc_strdup(const char *s1)
{
	int		l;
	int		i;
	char	*c;

	l = 0;
	i = 0;
	while (s1[l] != '\0')
	{
		l++;
	}
	c = (char *)gc_malloc((l + 1) * sizeof(char), getter());
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}