/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:10:33 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/02 18:20:17 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_error(const char *input, size_t i)
{
	if (i == 0 || input[i + 1] == '\0')
		return (1);
	if (input[i + 1] == '|')
		return (1);
	return (0);
}

int	check_redirect_error(const char *input, size_t i)
{
	if (input[i + 1] == '>' || input[i + 1] == '<' || input[i + 1] == '|')
		return (1);
	return (0);
}

void	skip_quotes(char *cmd, int *i)
{
	char	quote;

	quote = cmd[*i];
	(*i)++;
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i])
		(*i)++;
}

void	fill_result(char *cmd, int start, int end, char *result)
{
	int	k;

	k = 0;
	while (start < end)
	{
		if (cmd[start] != '\'' && cmd[start] != '\"')
			result[k++] = cmd[start];
		start++;
	}
	result[k] = '\0';
}
