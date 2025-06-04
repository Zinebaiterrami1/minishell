/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:52:14 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/03 11:10:23 by nel-khad         ###   ########.fr       */
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
	c = (char *)gc_malloc((l + 1) * sizeof(char), getter());
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
