/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:57:25 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 13:35:02 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lst_env(char **env, t_data *data)
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
			continue ;
		key = ft_substr(*env, 0, equal - *env);
		if (!key)
			error_lst_env(key, value, data);
		value = ft_strdup(equal + 1);
		if (!value)
			error_lst_env(key, value, data);
		node = ft_lst_env_new(key, value);
		if (!node)
			error_lst_env(key, value, data);
		ft_lst_env_add_back(&data->lst_env, node);
		env++;
	}
}
