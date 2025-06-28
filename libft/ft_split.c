/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:28:08 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/28 13:06:01 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\t' || s[i] == '\n')
			check = 0;
		else if (s[i] != c && check == 0)
		{
			count++;
			check = 1;
		}
		i++;
	}
	printf("cout word split = %d\n", count);
	return (count);
}size_t

static int	word_len(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c && str[len] != '\t'
		&& str[len] != '\n' && str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*alloc_cpy(const char *s, char c)
{
	char	*str;
	int		len;

	len = word_len(s, c);
	str = (char *)gc_malloc(sizeof(char) * (len + 1), getter());
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s, len);
	str[len] = '\0';
	return (str);
}

char	**ft_free(char **s, int i)
{
	while (--i >= 0)
		free(s[i]);
	free(s);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)gc_malloc(sizeof(char *) * (count_word(s, c) + 1),
			getter());
	if (!array)
		return (NULL);
	return (helper4(s, array, c));
}
