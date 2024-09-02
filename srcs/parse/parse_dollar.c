/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:51:30 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/02 19:12:19 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_dollar(const char *pos)
{
	t_mshell	e_code;
	
	// while(1)
	// {	
	if (*pos == '$' && *(pos + 1) == '$')
	{
		e_code.exit_code = getpid();
		printf("Your pid: %d\n", e_code.exit_code);
		// return (0);
	}
	else if (*pos == '$' && *(pos + 1) == '?')
	{
		e_code.exit_code = 0;	
		printf("Your last completed command: %d\n", e_code.exit_code);
		// return (0);
	}
	// return (0);
	// }
}

char	*append_var_to_result(char *result, const char *pos, size_t len)
{
	char	*new_result;
	size_t	var_name_len;
	char	*space_pos;

	space_pos = ft_strchr(pos + 1, ' ');
	if (space_pos != NULL)
		var_name_len = space_pos - (pos + 1);
	else
		var_name_len = ft_strlen(pos + 1);
	new_result = malloc(len + 1 + ft_strlen(pos + var_name_len) + 1);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	ft_memcpy(new_result, result, len);
	new_result[len] = '\0';
	ft_strncat(new_result, pos, var_name_len + 1);
	if (space_pos != NULL)
		ft_strcat(new_result, space_pos);
	free(result);
	// printf("here_is\n");
	return (new_result);
}

size_t	extract_var_name(const char *pos, char *var_name)
{
	size_t	i;

	i = 0;
	// pos++;
	while (pos[i] && pos[i] != ' ' && pos[i] != '\t' && pos[i] != '\n')
	{
		var_name[i] = pos[i];
		i++;
	}
	var_name[i] = '\0';
	return (i);
}

char	*replace_var_with_value(const char *input, const char *pos, t_env *env)
{
	char	*new_input;
	char	*value;
	char	var_name[256];
	size_t	var_len;
	size_t	new_len;
	
	pos++;
	var_len = extract_var_name(pos, var_name);
	value = get_env_val(var_name, env);
	if (!value)
	{
		if (*pos == '$' && (*(pos + 1) == '$' || *(pos + 1) == '?'))
			if_dollar(pos);
		printf("pos: %s%s\n", pos, pos + 1);
		new_len = (pos - input) + ft_strlen(pos + var_len) + 1;
		new_input = malloc(new_len);
		if (!new_input)
			return (NULL);
		new_input[0] = '\0';
		// strcpy(new_input, input);
		ft_memcpy(new_input, input, pos - input - 1);
		new_input[pos - input] = '\0';
		strcat(new_input, pos + var_len);
		// printf("here__\n");
		// printf("new_input: %s\n", new_input);
		return (new_input);
	}
	new_len = (pos - input - 1) + ft_strlen(value) + ft_strlen(pos + var_len);
	new_input = malloc(new_len + 1);
	if (!new_input)
		return (NULL);
	ft_memcpy(new_input, input, pos - input - 1);
	new_input[pos - input - 1] = '\0';
	strcat(new_input, value);
	strcat(new_input, pos + var_len);
	// printf("new_input: %s\n", new_input);
	return (new_input);
}

char	*expand_env_variables(const char *input, t_env *env)
{
	char	*result;
	char	*pos;
	char	*new_result;
	size_t	len;

	result = ft_strdup(input);
	if (!result)
		return (NULL);
	pos = result;
	while ((pos = ft_strchr(pos, '$')))
	{
		len = pos - result;
		new_result = replace_var_with_value(result, pos, env);
		if (!new_result)
		{
			free(result);
			return (NULL);
		}
		if (new_result == result)
			pos = result + len + 1;
		else
			pos = new_result + (pos - result) + (ft_strlen(new_result) - ft_strlen(result));
		free(result);
		result = new_result;
		// printf("here\n");
		// printf("result: %s\n", result);
	}
	return (result);
}

