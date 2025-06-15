/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:50:00 by myda-chi          #+#    #+#             */
/*   Updated: 2025/01/02 14:41:52 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}

// int	main(void)
// {
// 	t_list *first = ft_lstnew("hello");
// 	t_list *second = ft_lstnew("you");
// 	first->next = second;
// 	t_list *current;
// 	current = first;
// 	while (current)
// 	{
// 		printf("%s", current->content);
// 		current = current->next;
// 	}
// }