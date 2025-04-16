/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:59:29 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/16 15:58:24 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*curent;
	t_token	*next;

	if (!lst || !del)
		return ;
	curent = *lst;
	while (curent != NULL)
	{
		next = curent->next;
		ft_lstdelone(curent, del);
		curent = next;
	}
	*lst = NULL;
}
