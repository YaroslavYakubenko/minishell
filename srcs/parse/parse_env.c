/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:56:39 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/02 22:31:58 by yyakuben         ###   ########.fr       */
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
	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = ft_strndup(env_str, equal_sign - env_str);
	new_node->val = ft_strdup(equal_sign + 1);
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
	t_mshell	e_code;
	char	*str;

	name_len = ft_strlen(name);
	while (env)
	{
		// printf("env->name: %s\n", env->name);
		if (ft_strncmp(env->name, name, name_len) == 0 && env->name[name_len] == '\0')
		{
			
			// printf("env->val: %s\n", env->val);
			// printf("env->name: %s\n", env->name);
			// printf("name: %s\n", name);
			// printf("name_len: %zu\n", name_len);
			return (env->val);
		}
		else if (name[0] == '$')
		{
			// printf("Your last completed command: %d\n", e_code.exit_code);
			str = ft_itoa(e_code.exit_code);
			return (str);
		}
		else if (name[0] == '?')
		{
			// printf("Your pid: %d\n", getpid());
			str = ft_itoa(getpid());
			return (str);
		}
		env = env->next;
	}
	return (NULL);
}
