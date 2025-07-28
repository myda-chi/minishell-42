/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:50:36 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/28 14:57:29 by myda-chi         ###   ########.fr       */
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
