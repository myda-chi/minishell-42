/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:12:01 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/28 15:01:22 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_lenght(int n)
{
	unsigned int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static int	ft_fill_number(int n, char *str, int index)
{
	while (n > 0)
	{
		str[index] = (n % 10) + '0';
		n = n / 10;
		index--;
	}
	return (index);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;

	len = ft_get_lenght(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	ft_fill_number(n, str, len);
	return (str);
}
