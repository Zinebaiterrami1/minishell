/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:39:53 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/25 23:48:02 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(char *str)
{
	int	l;

	if (!str)
		return (0);
	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

static char	*helper2(char const *s1, char const *s2)
{
	char	*c;
	int		i;
	int		j;

	j = 0;
	i = 0;
	c = (char *)gc_malloc(sizeof(char) * (len((char *)s1) + len((char *)s2)
				+ 1), getter());
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		c[i++] = s2[j++];
	}
	c[i] = '\0';
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		if (!s2)
			return ((char *)s1);
		if (!s1)
			return ((char *)s2);
	}
	c = helper2(s1, s2);
	return (c);
}
