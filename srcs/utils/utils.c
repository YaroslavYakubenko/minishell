/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:41:13 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 18:28:13 by yyakuben         ###   ########.fr       */
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
