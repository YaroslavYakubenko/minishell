/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:56:39 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/30 16:08:31 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*temp;
	int		i;
	int		j;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = NULL;
	new_node->next = NULL;
	new_node->val = NULL;
	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	j = 0;
	temp = malloc((i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (env_str[j] && env_str[j] != '=')
	{
		temp[j] = env_str[j];
		j++;
	}
	temp[j] = '\0';
	new_node->name = temp;
	j = ++i;
	while (env_str[i])
		i++;
	temp = malloc((i - j + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = j;
	j = 0;
	while (env_str[i])
		temp[j++] = env_str[i++];
	temp[j] = '\0';
	new_node->val = temp;
	return (new_node);
}

void ft_free_double_pointer_char(char **output)
{
    int i = 0;
    while (output[i] != NULL)
    {
        free(output[i]);
        i++;
    }
    free(output);
}

t_env	*init_new_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;
	char	**store;
	
	i = 0;
	head = NULL;
	store = ft_renew_evnp(envp);
	store = ft_add_list(store);
	while (store[i])
	{
		new_node = create_env_node(store[i]);
		if (!new_node)
			return (head);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	ft_free_double_pointer_char(store);
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
		if (ft_strncmp(env->name, name, name_len) == 0 && env->name[name_len] == '\0')	
			return (env->val);
		else if (name[0] == '?')
		{
			e_code.exit_code = 0;
			str = ft_itoa(e_code.exit_code);
			return (str);
		}
		else if (name[0] == '$')
		{
			str = ft_itoa(getpid());
			return (str);
		}
		env = env->next;
	}
	return (NULL);
}

// char	*process_variable(char *result, char *pos, t_env *env, int in_single_quote)
// {
// 	char	*var_value;
// 	char	var_name[256];
// 	size_t	var_len;
// 	t_env	*temp;

// 	var_len = extract_var_name(pos + 1, var_name);
// 	if (in_single_quote)
// 		return (append_var_to_result(result, pos,var_len + 1));
// 	var_value = get_env_val(var_name, env);
// 	if (!var_value)
// 		return (create_new_str(result, var_len + 1, pos));
// 	while (env)
// 	{
// 		temp = env->next;
// 		free(env->name);
// 		free(env->next);
// 		free(env->val);
// 		free(env);
// 		env = temp;
// 	}
// 	return (replace_var_with_value(result, pos, var_value, var_len + 1));
// }

char *process_variable(char *result, char *pos, t_env *env, int in_single_quote)
{
    char *var_value;
    char var_name[256];
    size_t var_len;

    if (in_single_quote)
        return result;

    var_len = extract_var_name(pos + 1, var_name);
    var_value = get_env_val(var_name, env);
    if (!var_value)
        return create_new_str(result, var_len + 1, pos);
    return replace_var_with_value(result, pos, var_value, var_len + 1);
}

char	*update_position(char *result, char *new_result, char *pos)
{
	if (new_result == result)
		return (result + (pos - result) + 1);
	else
		return (new_result + (pos - result) + (ft_strlen(new_result) - ft_strlen(result)));
}
