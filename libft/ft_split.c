/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:28:49 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/28 14:56:24 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_aray(char **str, int i)
{
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return (0);
}

static int	count_substr(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*alloc_substr(const char *src, char c, int start)
{
	char	*dup;
	int		j;
	int		i;

	i = start;
	j = 0;
	while (src[i] && src[i] != c)
		i++;
	dup = (char *)malloc((i - start + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[start] && src[start] != c)
	{
		dup[j] = src[start];
		start++;
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**src;
	int		j;
	int		i;

	src = (char **)malloc((count_substr(s, c) + 1) * sizeof(char *));
	if (src == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			src[j] = alloc_substr(s, c, i);
			if (!src[j])
				return (free_aray(src, i), NULL);
			j++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	src[j] = NULL;
	return (src);
}
