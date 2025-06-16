/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:52:14 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/16 13:36:49 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*ft_strdup(const char *s1)
{
	int		l;
	int		i;
	char	*c;

	l = 0;
	i = 0;
	if(!s1)
		return(NULL);
	while (s1[l] != '\0')
	{
		l++;
	}
	c = (char *)malloc((l + 1) * sizeof(char));
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
