/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:22:02 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/28 14:56:59 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*src;
	unsigned char	n;

	n = (unsigned char)c;
	src = (char *)s;
	while (*src)
	{
		if ((unsigned char)*src == n)
			return (src);
		src++;
	}
	if (n == 0)
		return (src);
	return (0);
}
