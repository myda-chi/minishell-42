/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:50:49 by myda-chi          #+#    #+#             */
/*   Updated: 2025/01/02 14:45:19 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// void to_uppercase(unsigned int index, char *c)
// {
//     *c=ft_toupper(*c);
// }
// #include <stdio.h>
// int main()
// {
//     char str[]="helloyou";
// 	ft_striteri(str, to_uppercase);
//     printf("%s",str);

// }