/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:10:48 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/05 18:13:04 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_env_name(char *env_str)
{
	char	*name;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
	{
		name[i] = env_str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*extract_env_value(char *env_str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (!env_str[i])
		return (NULL);
	i++;
	j = i;
	while (env_str[i])
		i++;
	value = malloc((i - j + 1) * sizeof(char));
	if (!value)
		return (NULL);
	i = j;
	j = 0;
	while (env_str[i])
		value[j++] = env_str[i++];
	value[j] = '\0';
	return (value);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = NULL;
	new_node->next = NULL;
	new_node->val = NULL;
	new_node->name = extract_env_name(env_str);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->val = extract_env_value(env_str);
	new_node->next = NULL;
	return (new_node);
}
