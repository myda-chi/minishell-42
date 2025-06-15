/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:05:38 by myda-chi          #+#    #+#             */
/*   Updated: 2025/01/07 11:35:36 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*str;
	unsigned int	p;

	p = ft_strlen(s);
	i = 0;
	if (start >= p)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (start + len > p)
		len = p - start;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>
// int main()
// {
//     char ptr[]="hello yda42";
//     int start=2;
//     printf("%s", ft_substr(ptr, start, 8));
// }
