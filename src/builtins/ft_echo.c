/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:40:00 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/19 21:09:24 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_n_flag(char *arg)
{
	return (ft_strncmp(arg, "-n", 2) == 0);
}

static void	print_arguments(int argc, char **argv, int start_index)
{
	int	i;

	i = start_index;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i < argc - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

static void	print_newline_if_needed(int n_flag)
{
	if (!n_flag)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (argc > 1 && check_n_flag(argv[1]))
	{
		n_flag = 1;
		i++;
	}
	print_arguments(argc, argv, i);
	print_newline_if_needed(n_flag);
	return (0);
}
