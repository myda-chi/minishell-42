/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:13:21 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/28 15:02:01 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*content;
	t_list	*newnode;
	t_list	*newlist;

	newlist = NULL;
	while (lst)
	{
		content = f(lst->content);
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			del(content);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}

void	*ft_tupper(void *s)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (s);
}

void	fdel(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*new;
	int		third;

	first = ft_lstnew(ft_strdup("hello"));
	second = ft_lstnew(ft_strdup("you"));
	ft_lstadd_back(&first, second);
	ft_lstadd_back(&first, ft_lstnew(ft_strdup("42ad")));
	third = ft_lstsize(first);
	printf("%d\n", third);
	new = ft_lstmap(first, ft_tupper, fdel);
	while (new)
	{
		printf("%s\n", new->content);
		new = new->next;
	}
	ft_lstclear(&first, free);
	return (0);
}
