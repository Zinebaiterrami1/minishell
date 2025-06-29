/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:17:53 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/29 01:28:18 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node(t_garbage **list, t_garbage *new)
{
	if (!list || !(*list))
	{
		*list = new;
		return ;
	}
	new->next = *list;
	*list = new;
	return ;
}

void	*gc_malloc(size_t size, t_garbage **list)
{
	void		*ptr;
	t_garbage	*new;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->next = NULL;
	new->adress = ptr;
	add_node(list, new);
	return (ptr);
}

t_garbage	**getter(void)
{
	static t_garbage	*gc;

	return (&gc);
}

void	free_all(t_garbage **list)
{
	t_garbage	*next;

	while ((*list))
	{
		if ((*list)->adress)
			free((*list)->adress);
		next = (*list)->next;
		if ((*list))
			free((*list));
		(*list) = next;
	}
	*list = NULL;
}
