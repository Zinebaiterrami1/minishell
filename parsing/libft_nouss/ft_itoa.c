/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:11:47 by nel-khad          #+#    #+#             */
/*   Updated: 2024/11/11 11:35:59 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*conv_str(long nb, int len, char *s)
{
	if (nb < 0)
	{
		nb = -nb;
		s[0] = '-';
	}
	s[len--] = '\0';
	if (nb == 0)
	{
		s[0] = '0';
		return (s);
	}
	while (nb > 0)
	{
		s[len] = '0' + (nb % 10);
		nb = nb / 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int nbr)
{
	char	*s;
	long	nb;
	int		len;

	nb = nbr;
	len = len_(nb);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s = conv_str(nb, len, s);
	return (s);
}
