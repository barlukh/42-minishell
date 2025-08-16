/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/16 16:40:44 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_exec *current)
{
	char	pwd[PATH_MAX];
	size_t	i;

	i = 0;
	if (ft_strcmp(current->cmd_arg[i], "cd") == 0)
	{
		getcwd(pwd, PATH_MAX);
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (BUILT_YES);
	}
	return (BUILT_NO);
}
