/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/04 17:59:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_token **current, t_data *data)
{
	char	pwd[PATH_MAX];

	(void)data;
	if (ft_strcmp((*current)->content, "cd") == 0)
	{
		getcwd(pwd, PATH_MAX);
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (BUILT_YES);
	}
	return (BUILT_NO);
}
