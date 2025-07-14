/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:41:05 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 21:41:49 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
#include <unistd.h>

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

static void	print_pwd_error(void)
{
	perror("pwd");
}

static int	get_and_print_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	print_pwd_error();
	return (1);
}

int	ft_pwd(void)
{
	return (get_and_print_pwd());
}
