/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:18:39 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/03 19:32:18 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_space(char *input, int i)
{
	int		j;
	char	*output;

	j = ft_strlen(input);
	output = malloc((j + 2) * sizeof(char));
	if (!output)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		output[j] = input[j];
		j++;
	}
	output[j] = ' ';
	i++;
	j++;
	while (input[i])
		output[j++] = input[i++];
	output[j] = '\0';
	free(input);
	return (output);
}

char	*ft_be_nice(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] != ' ')
			input = ft_add_space(input, i + 1);
		else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] != ' ')
			input = ft_add_space(input, i + 1);
		else if (input[i] == '<' && input[i + 1] != ' ')
			input = ft_add_space(input, i);
		else if (input[i] == '>' && input[i + 1] != ' ')
			input = ft_add_space(input, i);
		else if (input[i] == '|' && input[i + 1] != ' ')
			input = ft_add_space(input, i);
		i++;
	}
	return (input);
}

int	is_empty_or_space_only(const char *input)
{
	while (*input)
	{
		if (*input != ' ')
			return (0);
		input++;
	}
	return (1);
}