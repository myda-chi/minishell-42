/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:21 by myda-chi          #+#    #+#             */
/*   Updated: 2024/12/30 14:18:08 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned const char	*s;

	s = (unsigned const char *)src;
	d = (unsigned char *)dst;
	if (d == s)
		return (dst);
	if (d < s || d >= s + len)
	{
		while (len--)
			*(d++) = *(s++);
	}
	else
	{
		d += len - 1;
		s += len - 1;
		while (len--)
			*(d--) = *(s--);
	}
	return (dst);
}

// //  #include <stdio.h>
// //  int main()
// //  {
// //     char s[]="abcdefghij";
// //     char d[20];
// //     printf("%s", ft_memmove(s +5, s, 3));
//  }