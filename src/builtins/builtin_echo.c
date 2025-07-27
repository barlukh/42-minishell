/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:27:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/27 17:24:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_token **current)
{
	if (ft_strcmp((*current)->content, "echo") == 0)
	{
		if (((*current)->next)
			&& ft_strcmp((*current)->next->content, "-n") == 0)
		{
			(*current) = (*current)->next;
			if (((*current)->next) && (*current)->next->type == TOK_WORD)
			{
				(*current) = (*current)->next;
				ft_putstr_fd((*current)->content, 1);
			}
			else
				ft_putstr_fd("", 1);
		}
		else if (((*current)->next) && (*current)->next->type == TOK_WORD)
		{
			(*current) = (*current)->next;
			ft_putendl_fd((*current)->content, 1);
		}
		else
			ft_putendl_fd("", 1);
		return (BUILT_YES);
	}
	return (BUILT_NO);
}
