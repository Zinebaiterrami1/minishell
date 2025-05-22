/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:04:24 by nel-khad          #+#    #+#             */
/*   Updated: 2024/11/11 09:52:38 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	end(const char *s, const char *set)
{
	size_t	i;
	int		j;

	i = ft_strlen(s) - 1;
	j = 0;
	while (i > 0 && set[j])
	{
		if (s[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start_i;
	int		len;
	int		i;
	int		end_i;
	char	*ss;

	i = 0;
	len = 0;
	if (!set && s1)
		return ((char *)s1);
	if (!s1)
		return (ft_strdup(""));
	start_i = start(s1, set);
	end_i = end(s1, set);
	if (end_i > start_i)
		len = end_i - start_i + 1;
	ss = (char *)malloc((len + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	while (start_i <= end_i)
		ss[i++] = s1[start_i++];
	ss[i] = '\0';
	return (ss);
}
