/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:30:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 23:57:16 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **helper4(const char *s, char **array, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			array[j] = alloc_cpy(s + i, c);
			if (array[j++] == NULL)
				return (ft_free(array, j));
		}
		while (s[i] && s[i] != c)
			i++;
	}
    return (array[j] = NULL, array);
}
