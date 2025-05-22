/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:07:51 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/24 17:00:39 by nel-khad         ###   ########.fr       */
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
	return;
	// printf("node aded -> %s\n", ptr->value);
}
