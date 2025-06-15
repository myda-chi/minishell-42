/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:50:36 by myda-chi          #+#    #+#             */
/*   Updated: 2024/12/28 19:08:50 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	s;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (dstsize <= i)
	{
		return (dstsize + j);
	}
	s = 0;
	while (src[s] && i + s < dstsize - 1)
	{
		dst[i + s] = src[s];
		s++;
	}
	dst[s + i] = '\0';
	return (i + j);
}

// #include <stdio.h>
// int main()
// {
//     char s[]="halo,you";
//     char d[10]="hey";
//     printf("%zu\n%s", ft_strlcat(d, s, 10), d);
//     // printf("%zu\n", strlcat(d, s, 10));
// }
