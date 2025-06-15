/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:14:26 by myda-chi          #+#    #+#             */
/*   Updated: 2025/01/02 14:50:09 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
// int main()
// {
// 	t_list *first=ft_lstnew("hello");
// 	t_list *second=ft_lstnew("you");
// 	first->next=second;
// 	t_list *third=ft_lstnew("world");
// 	ft_lstadd_front(&first, third);
// 	t_list *current=third;
// 	while(current)
// 	{
// 		printf("%s\n", current->content);
// 		current=current->next;
// 	}
// }
