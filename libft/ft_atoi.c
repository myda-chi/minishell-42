/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:52:23 by myda-chi          #+#    #+#             */
/*   Updated: 2024/12/30 15:13:33 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;
	int					i;

	sign = 1;
	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (sign == -1 && num >= LLONG_MAX)
			return (0);
		if (num >= LLONG_MAX)
			return (-1);
		i++;
	}
	return (num * sign);
}

// #include <stdio.h>
// int main(void)
// {
//  printf("%d\n",ft_atoi("  3147483648887"));
//  printf("%d", atoi("  3147483648887"));
// }