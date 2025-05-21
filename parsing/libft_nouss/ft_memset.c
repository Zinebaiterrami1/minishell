/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:12:39 by nel-khad          #+#    #+#             */
/*   Updated: 2024/11/09 14:22:12 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	uc;

	p = (unsigned char *)str;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		p[i] = uc;
		i++;
	}
	return (str);
}
