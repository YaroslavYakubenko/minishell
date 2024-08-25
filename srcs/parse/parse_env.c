/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:56:39 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/23 12:04:19 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = strchr(env_str, '=');
	if (!equal_sign)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = strndup(env_str, equal_sign - env_str);
	new_node->val = strdup(equal_sign + 1);
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_new_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;
	
	i = 0;
	head = NULL;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
			return (head);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

char	*get_env_val(const char *name, t_env *env)
{
	size_t	name_len;

	name_len = strlen(name);
	while (env)
	{
		if (strncmp(env->name, name, name_len) == 0 && env->name[name_len] == '\0')
			// printf("env->val: %s\n", env->val);
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
