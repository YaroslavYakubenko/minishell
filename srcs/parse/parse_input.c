/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:40:27 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/03 22:12:43 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(char **evnp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_nbr = 0;
	cmd->pipe_nbr = 0;
	cmd->before_pipe = 0;
	cmd->after_pipe = 0;
	cmd->input = 0;
	cmd->output = 0;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->evnp = evnp;
	cmd->next = NULL;
	return (cmd);
}

int	ft_get_parts(char *cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i = handle_quote(cmd, i, cmd[i]);
			k++;
		}
		else if (cmd[i] == ' ')
			i++;
		else
		{
			k++;
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\'' && cmd[i] != '\"')
				i++;
		}
	}
	return (k);
}

t_cmd	*create_and_fill_cmd(char *cmd, char **evnp)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd(evnp);
	if (!new_cmd)
		return (NULL);
	free(new_cmd->args);
	new_cmd->args = ft_deal_cmd(cmd);
	return (new_cmd);
}

static void	add_command_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *cmd_list;
	if (!tmp)
		*cmd_list = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

t_cmd	*ft_start_parse(char *cmd_line, char **evnp)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	char	*cmd;
	int		i;

	i = 0;
	cmd_list = NULL;
	// if (has_invalid_pipe_syntax(cmd))
	// {
	// 	printf("Error: syntax error with pipe or redirections\n");
	// 	return (NULL);
	// }
	if (is_empty_or_space_only(cmd_line))
		return (NULL);
	while (i <= (int)ft_strlen(cmd_line) && cmd_line[i])
	{
		cmd = extract_command(cmd_line, &i);
		if (!cmd)
			return (NULL);
		new_cmd = create_and_fill_cmd(cmd, evnp);
		free(cmd);
		if (!new_cmd)
			return (NULL);
		add_command_to_list(&cmd_list, new_cmd);
	}
	free(cmd_line);
	return (cmd_list);
}
