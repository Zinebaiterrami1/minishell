/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:07:51 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/25 23:11:55 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*ptr;

	if (new == NULL || !token)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	ptr = ft_lstlast(*token);
	if (ptr)
		ptr->next = new;
	return ;
}
