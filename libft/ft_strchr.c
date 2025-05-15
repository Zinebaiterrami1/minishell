/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:37:57 by zait-err          #+#    #+#             */
/*   Updated: 2024/11/13 08:18:55 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	z;

	z = (char)c;
	while (*str != '\0')
	{
		if (*str == z)
			return ((char *)str);
		str++;
	}
	if (*str == z)
		return ((char *)str);
	return (NULL);
}
