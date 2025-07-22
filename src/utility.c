/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:38:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 17:54:55 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_key_value(char *env, t_env **lst_env, char *equal, t_env **node);

void	create_lst_env(char **env, t_env **lst_env)
{
	char	*equal;
	t_env	*node;

	while (*env)
	{
		node = NULL;
		equal = ft_strchr(*env, '=');
		if (equal)
			get_key_value(*env, lst_env, equal, &node);
		ft_lst_env_add_back(lst_env, node);
		env++;
	}
}

static void	get_key_value(char *env, t_env **lst_env, char *equal, t_env **node)
{
	char	*key;
	char	*value;

	key = ft_substr(env, 0, equal - env);
	if (!key)
		exit(error_lst_env(lst_env));
	value = ft_strdup(equal + 1);
	if (!value)
	{
		free(key);
		exit(error_lst_env(lst_env));
	}
	*node = ft_lst_env_new(key, value);
}
