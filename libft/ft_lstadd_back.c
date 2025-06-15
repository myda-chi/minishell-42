/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:41:49 by myda-chi          #+#    #+#             */
/*   Updated: 2025/01/02 14:47:09 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
// int main()
// {
// 	t_list *first=ft_lstnew("hello");
// 	t_list *second=ft_lstnew("you");
// 	first->next=second;
// 	t_list *third=ft_lstnew("world");
// 	ft_lstadd_back(&first, third);
// 	t_list *current=first;
// 	while(current)
// 	{
// 		printf("%s", current->content);
// 		current=current->next;
// 	}

// }