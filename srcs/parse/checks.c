/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:10:33 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/04 21:51:34 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_quotes(const char *cmd_line, int *i,
	int *in_single_quote, int *in_double_quote)
{
	if (cmd_line[*i] == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (cmd_line[*i] == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

int	check_pipe_or_redirect(const char *cmd_line, int *i)
{
	if (cmd_line[*i] == '|' && *i == 0)
		return (1);
	if (cmd_line[*i] == '|' && cmd_line[*i + 1] == '|')
		return (1);
	if (cmd_line[*i] == '|' && !cmd_line[*i + 1])
		return (1);
	return (0);
}

int	has_invalid_pipe_or_redirects(const char *cmd_line)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (cmd_line[i])
	{
		handle_quotes(cmd_line, &i, &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote)
		{
			if (check_pipe_or_redirect(cmd_line, &i))
				return (1);
		}
		i++;
	}
	return (0);
}
