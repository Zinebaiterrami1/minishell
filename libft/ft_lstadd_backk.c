/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_backk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:40:11 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 23:12:47 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_backk(t_env **env, t_env *new)
{
	t_env	*ptr;

	if (new == NULL || !env)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	ptr = ft_lstlastt(*env);
	if (ptr)
		ptr->next = new;
	return ;
}
