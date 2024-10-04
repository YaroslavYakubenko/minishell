/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mark_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:50:24 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/04 22:47:35 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_double_redirect(char *cmd_line, int i)
{
	if (cmd_line[i + 2] == ' ')
		i += 3;
	else
		i += 2;
	while (cmd_line[i] && cmd_line[i] != ' ')
		i++;
	i++;
	return (i);
}

int	handle_single_redirect(char *cmd_line, int i)
{
	if (cmd_line[i + 1] == ' ')
		i += 2;
	else
		i += 1;
	while (cmd_line[i] && cmd_line[i] != ' ')
		i++;
	i++;
	return (i);
}

int	handle_normal(char *cmd_line, int i)
{
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'')
		{
			i++;
			while (cmd_line[i] && cmd_line[i] != '\'')
				i++;
		}
		else if (cmd_line[i] == '\"')
		{
			i++;
			while (cmd_line[i] && cmd_line[i] != '\"')
				i++;
		}
		else
		{
			while (cmd_line[i] && cmd_line[i] != '|'
				&& cmd_line[i] != '<' && cmd_line[i] != '>')
				i++;
			return (i);
		}
	}
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
	{
		if (cmd_line[i + 1] == ' ')
			return (i + 2);
		else
			return (i + 1);
	}
	else
		return (handle_normal(cmd_line, i));
	return (i);
}

char	*create_command_substring(const char *cmd_line, int j, int i)
{
	char	*cmd;

	cmd = malloc(sizeof(char) * (i - j + 1));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, &cmd_line[j], i - j + 1);
	cmd = ft_be_nice(cmd);
	return (cmd);
}
