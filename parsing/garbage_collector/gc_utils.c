/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:17:53 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/20 10:11:51 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_garbage	*get_last_node(t_garbage *list)
{
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

t_garbage	*get_adress(void *adress, t_garbage *list)
{
	while (list)
	{
		if (list->adress == adress)
			return (list);
		list = list->next;
	}
	return (list);
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