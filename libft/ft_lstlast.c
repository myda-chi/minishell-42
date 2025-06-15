/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:36:21 by myda-chi          #+#    #+#             */
/*   Updated: 2025/01/03 13:35:28 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
// int	main(void)
// {
// 	t_list *first = ft_lstnew("hello");
// 	t_list *second = ft_lstnew("you");
// 	first->next = second;
// 	t_list *current;
// 	current = ft_lstlast(first);
// 	while (current)
// 	{
// 		printf("%s", (char *)current->content);
// 		current = current->next;
// 	}
// }