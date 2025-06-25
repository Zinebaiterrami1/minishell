/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:37:52 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/25 23:12:38 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_env *lst)
{
	int		count;
	t_env	*tmp;

	tmp = lst;
	count = 0;
	if (!lst)
		return (0);
	while (tmp)
		tmp = tmp->next;
	while (lst != NULL)
	{
		count++;
		lst->is_printed = 0;
		lst = lst->next;
	}
	return (count);
}
