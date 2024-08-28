/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:51:30 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/28 20:38:49 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	if_dollar(char *pos)
{
	t_mshell	e_code;
	
	// while(1)
	// {	
	if (*pos == '$' && *(pos + 1) == '$')
	{
		e_code.exit_code = getpid();
		printf("Your pid: %d\n", e_code.exit_code);
		return (0);
	}
	else if (*pos == '$' && *(pos + 1) == '?')
	{
		e_code.exit_code = 0;	
		printf("Your last completed command: %d\n", e_code.exit_code);
		return (0);
	}
	return (*pos);
	// }
}

char	*expand_env_variables(const char *input, t_env *env)
{
	char	*result;
	char	*pos;
	char	*new_result;
	// t_mshell		e_code;

	result = strdup(input);
	if (!result)
		return (NULL);
	pos = result;
	while ((pos = strchr(pos, '$')))
	{
		new_result = replace_var_with_value(result, pos, env);
		if (!new_result)
		{
			free(result);
			return (NULL);
		}
		if (new_result == result)
			pos++;
		else
			pos = new_result + (pos - result) + (strlen(new_result) - strlen(result));
		free(result);
		result = new_result;
	}
	return (result);
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
	// printf("new_input: %s\n", new_input);
	return (new_input);
}

