/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:11:23 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/20 10:48:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	export_action(char *content, t_data *data);

void	export_loop(bool *inv_id, char *content, t_data *data)
{
	size_t	i;

	(void)data;
	i = 0;
	if (!ft_isalpha(content[i]) && content[i] != '_')
	{
		*inv_id = true;
		ft_putendl_fd(ERR_MSG_IDEN, STDERR_FILENO);
		return ;
	}
	else
	{
		while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
			i++;
	}
	if (content[i] != '\0' && !(content[i] == '+' && content[i + 1] == '=')
		&& content[i] != '=')

	{
		*inv_id = true;
		ft_putendl_fd(ERR_MSG_IDEN, STDERR_FILENO);
		return ;
	}
	// export_action(content, data);
	return ;
}

// Performs the export action.
// static void	export_action(char *content, t_data *data)
// {
// 	char	*equal;
// 	char	*key;
// 	char	*value;
// 	t_env	*node;

// 	key = NULL;
// 	value = NULL;
// 	equal = ft_strchr(content, '=');
// 	if (!equal)
// 		key = content;
// 	else
// 		key = ft_substr(content, 0, equal - *content);
// 	if (!key)
// 		error_lst_env(key, value, data);
// 	value = ft_strdup(equal + 1);
// 	if (!value)
// 		error_lst_env(key, value, data);
// 	node = ft_lst_env_new(key, value);
// 	if (!node)
// 		error_lst_env(key, value, data);
// 	ft_lst_env_add_back(&data->lst_env, node);
// }

void	error_export(char *str_arg, char *key, char *value, t_data *data)
{
	free(str_arg);
	str_arg = NULL;
	free(key);
	key = NULL;
	free(value);
	value = NULL;
	clean_data(data);
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}
