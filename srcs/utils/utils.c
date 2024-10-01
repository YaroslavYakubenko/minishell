/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:41:13 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 19:02:32 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlenn(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != ' ' && str[len] != '\0')
		len++;
	return (len);
}

char	*allocate_new_input(size_t len)
{
	char	*new_input;

	new_input = malloc(len + 1);
	if (!new_input)
	{
		printf("Memory allocation failed\n");
		return (NULL);
	}
	return (new_input);
}

char	*update_position(char *result, char *new_result, char *pos)
{
	if (new_result == result)
		return (result + (pos - result) + 1);
	else
		return (new_result + (pos - result)
			+ (ft_strlen(new_result) - ft_strlen(result)));
}

int	handle_dollar_sign(char **result, char **pos, t_env *env, int quotes[2])
{
	char	*new_result;

	if (**pos == '$' && (quotes[1] || !quotes[0]))
	{
		new_result = process_variable(*result, *pos, env, quotes[0]);
		if (!new_result)
		{
			free(*result);
			*result = NULL;
			return (1);
		}
		*pos = new_result + (*pos - *result);
		free(*result);
		*result = new_result;
		return (0);
	}
	return (0);
}
