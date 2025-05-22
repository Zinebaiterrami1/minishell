/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:06:32 by nel-khad          #+#    #+#             */
/*   Updated: 2024/11/11 13:00:47 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *word, size_t len)
{
	size_t	i;
	int		j;
	char	*s;

	i = 0;
	s = (char *)str;
	if (word[0] == 0)
		return ((char *)str);
	if (!str && !len)
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		j = 0;
		while (s[i + j] == word[j] && s[i + j] && (i + j) < len)
			j++;
		if (word[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
