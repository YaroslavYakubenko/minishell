/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:56:39 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/17 15:51:21 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env	*parse_env_var(const char *env_str)
// {
// 	char	*equal_sign;
// 	t_env	*env_var;

// 	equal_sign = ft_strchr(env_str, '=');
// 	if (!equal_sign || equal_sign == env_str)	
// 		return (NULL);
// 	env_var = malloc(sizeof(t_env));
// 	if (!env_var)
// 		return (NULL);
// 	env_var->name = strndup(env_str, equal_sign - env_str);
// 	env_var->val = strdup(equal_sign + 1);
// 	if (!env_var->name || !env_var->val)
// 	{
// 		free(env_var->name);
// 		free(env_var->val);
// 		free(env_var);
// 		return (NULL);
// 	}
// 	return (env_var);
// }

// void	free_env_var(t_env *env_var)
// {
// 	free(env_var->name);
// 	free(env_var->val);
// 	free(env_var);
// }

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

char	*replace_var_with_value(const char *input, const char *pos, t_env *env)
{
	char	*new_input;
	char	*value;
	char	var_name[256];
	size_t	var_len;
	size_t	new_len;
	
	pos++;
	var_len = 0;
	while (pos[var_len] && pos[var_len] != ' ' && pos[var_len] != '\t' && pos[var_len] != '\n')
		var_len++;
	strncpy(var_name, pos, var_len);
	var_name[var_len] = '\0';
	value = get_env_val(var_name, env);
	if (!value)
		return (strdup(input));
	new_len = (pos - input - 1) + strlen(value) + strlen(pos + var_len) + 1;
	new_input = malloc(new_len);
	if (!new_input)
		return (NULL);
	// printf("here\n");
	memcpy(new_input, input, pos - input - 1);
	new_input[pos - input - 1] = '\0';
	strcat(new_input, value);
	strcat(new_input, pos + var_len);
	return (new_input);
}

