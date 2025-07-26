/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:57:25 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/26 15:52:19 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_lst_env(char **env, t_env **lst_env)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*node;

	key = NULL;
	value = NULL;
	while (*env)
	{
		equal = ft_strchr(*env, '=');
		if (!equal)
			exit(error_lst_env(FAILURE, key, value, lst_env));
		key = ft_substr(*env, 0, equal - *env);
		if (!key)
			exit(error_lst_env(FAILURE, key, value, lst_env));
		value = ft_strdup(equal + 1);
		if (!value)
			exit(error_lst_env(FAILURE, key, value, lst_env));
		node = ft_lst_env_new(key, value);
		if (!node)
			exit(error_lst_env(FAILURE, key, value, lst_env));
		ft_lst_env_add_back(lst_env, node);
		env++;
	}
}
