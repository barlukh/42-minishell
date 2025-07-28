/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/28 15:31:16 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd_pointers(t_env **old_pwd, t_env **pwd, t_env **lst_env);
static void	change_pwd(t_env **old_pwd, t_env **pwd);

int	builtin_cd(t_env **lst_env, t_token **current)
{
	t_env	*old_pwd;
	t_env	*pwd;
	
	if (ft_strcmp((*current)->content, "cd") == 0)
	{
		old_pwd = NULL;
		pwd = NULL;
		set_pwd_pointers(lst_env, &old_pwd, &pwd);
		if (((*current)->next)
			&& ft_strcmp((*current)->next->content, "-") == 0)
			change_pwd(&old_pwd, &pwd);
		return (BUILT_YES);
	}
	return (BUILT_NO);
}

static void	set_pwd_pointers(t_env **old_pwd, t_env **pwd, t_env **lst_env)
{
	t_env	*current;

	current = *lst_env;
	while(current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			*old_pwd = current;
		else if (ft_strcmp(current->key, "PWD") == 0)
			*pwd = current;
		current = current->next;
	}
}

static void	change_pwd(t_env **old_pwd, t_env **pwd)
{
	*pwd = *old_pwd;
}
