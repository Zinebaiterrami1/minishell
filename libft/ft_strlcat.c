/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:40:19 by nel-khad          #+#    #+#             */
/*   Updated: 2024/11/07 20:28:30 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lens;
	size_t	lend;

	lend = 0;
	lens = 0;
	while (dest[lend] != '\0')
		lend++;
	while (src[lens] != '\0')
		lens++;
	if (size == 0 || size <= lend)
		return (lens + size);
	i = 0;
	j = lend;
	while (src[i] && i < size - lend - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (lens + lend);
}
