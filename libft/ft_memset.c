/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:03:07 by zait-err          #+#    #+#             */
/*   Updated: 2024/11/08 09:28:59 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	value;

	i = 0;
	str = (unsigned char *)p;
	value = (unsigned char)c;
	while (i < n)
	{
		str[i] = value;
		i++;
	}
	return (p);
}
