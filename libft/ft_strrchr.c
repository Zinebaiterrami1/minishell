/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:57 by nel-khad          #+#    #+#             */
/*   Updated: 2024/11/09 14:52:26 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cc;
	unsigned int	i;
	const char		*res;

	res = NULL;
	i = 0;
	cc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			res = &s[i];
		i++;
	}
	if (s[i] == cc)
		res = &s[i];
	return ((char *)res);
}
