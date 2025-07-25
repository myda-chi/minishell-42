/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:20:00 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 19:22:55 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_syntax_error(char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
