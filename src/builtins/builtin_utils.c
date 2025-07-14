/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:39:06 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 21:39:11 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_cd_error(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	print_export_error(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

char	*extract_value(char *eq_pos)
{
	return (ft_strdup(eq_pos + 1));
}
