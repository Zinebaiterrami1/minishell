/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:42:33 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/02 13:59:27 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->env_key = key;
	list->env_value = value;
    list->next = NULL;
	return (list);
}
