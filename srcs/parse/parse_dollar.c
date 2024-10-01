/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:51:30 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 19:02:53 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (result)
			free(result);
		return (NULL);
	}
	ft_memcpy(new_result, result, len);
	new_result[len] = '\0';
	ft_strncat(new_result, pos, var_name_len + 1);
	if (space_pos != NULL)
		ft_strcat(new_result, space_pos);
	if (result)
		free(result);
	return (new_result);
}

size_t	extract_var_name(const char *pos, char *var_name)
{
	size_t	i;

	i = 0;
	while (pos[i] && pos[i] != ' ' && pos[i] != '\t' && pos[i] != '\n'
		&& pos[i] != '$' && pos[i] != '\'' && pos[i] != '\"')
	{
		var_name[i] = pos[i];
		i++;
	}
	var_name[i] = '\0';
	return (i);
}

char	*replace_var_with_value(const char *input,
	const char *pos, char *value, size_t var_len)
{
	char	*new_input;
	size_t	new_len;

	if (!value)
		value = "";
	new_len = (pos - input) + ft_strlen(value) + ft_strlen(pos + var_len);
	new_input = allocate_new_input(new_len);
	ft_memcpy(new_input, input, pos - input);
	new_input[pos - input] = '\0';
	ft_strcat(new_input, value);
	ft_strcat(new_input, pos + var_len);
	return (new_input);
}

char	*expand_env_variables(const char *input, t_env *env)
{
	char	*result;
	char	*pos;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	result = ft_strdup(input);
	if (!result)
		return (NULL);
	pos = result;
	while (*pos)
	{
		check_quotes(*pos, &quotes[0], &quotes[1]);
		if (handle_dollar_sign(&result, &pos, env, quotes))
			return (result);
		pos++;
	}
	return (result);
}

char	*create_new_str(const char *input, size_t var_len, const char *pos)
{
	char	*new_input;
	size_t	new_len;

	new_len = (pos - input) + ft_strlen(pos + var_len) + 1;
	new_input = malloc(new_len);
	if (!new_input)
		return (NULL);
	ft_memcpy(new_input, input, pos - input);
	new_input[pos - input] = '\0';
	ft_strcat(new_input, pos + var_len);
	return (new_input);
}
