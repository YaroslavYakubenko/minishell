/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mark_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:50:24 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 17:48:19 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_double_redirect(char *cmd_line, int i)
{
	i += 3;
	while (cmd_line[i] && cmd_line[i] != ' ')
		i++;
	i++;
	return (i);
}

int	handle_single_redirect(char *cmd_line, int i)
{
	i += 2;
	while (cmd_line[i] && cmd_line[i] != ' ')
		i++;
	i++;
	return (i);
}

int	ft_find_end(char *cmd_line, int i)
{
	if ((cmd_line[i] == '>' && cmd_line[i + 1] == '>')
		|| (cmd_line[i] == '<' && cmd_line[i + 1] == '<'))
		return (handle_double_redirect(cmd_line, i));
	else if (cmd_line[i] == '>' || cmd_line[i] == '<')
		return (handle_single_redirect(cmd_line, i));
	else if (cmd_line[i] == '|')
		return (i + 2);
	else
	{
		while (cmd_line[i] && cmd_line[i] != '|'
			&& cmd_line[i] != '<' && cmd_line[i] != '>')
			i++;
	}
	return (i);
}

char	*create_command_substring(const char *cmd_line, int j, int i)
{
	char	*cmd;

	cmd = malloc(sizeof(char) * (i - j + 1));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, &cmd_line[j], i - j + 1);
	return (cmd);
}

char	*extract_command(char *cmd_line, int *i)
{
	int	j;

	j = *i;
	*i = ft_find_end(cmd_line, *i);
	return (create_command_substring(cmd_line, j, *i));
}
