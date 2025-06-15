/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:37:52 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/15 18:21:05 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_env *lst)
{
	int	count;
	t_env *tmp;
	
	tmp = lst;
	count = 0;
	if (!lst)
		return (0);
	while(tmp)
	{
		// printf("key: %s\n", tmp->env_key);
		tmp = tmp->next;
	}
	while (lst != NULL)
	{
		count++;
		lst->is_printed = 0;
		lst = lst->next;
	}
	// printf("count: %d\n", count);
	return (count);
}
