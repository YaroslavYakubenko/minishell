/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:40:27 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/20 22:38:43 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
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
	cmd->next = NULL;
	return (cmd);
}

void	ft_print_doulbe_pointer(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	**ft_deal_cmd(char *cmd)
{
	char	**args;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	k = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && cmd[i] == '\"')
			j = 1;
		i++;
	}
	if (j == 1)
		args = ft_split(cmd, ' ');
	else
	{
		i = 0;
		while (cmd[i])
		{
			if (cmd[i] == '\'')
			{
				i++;
				k++;
				while (cmd[i] && cmd[i] != '\'')
					i++;
				i++;
			}
			else if (cmd[i] == '\"')
			{
				i++;
				k++;
				while (cmd[i] && cmd[i] != '\"')
					i++;
				i++;
			}
			else if(cmd[i] == ' ')
				i++;
			else if(cmd[i] != ' ')
			{
				k++;
				while (cmd[i] && cmd[i] != ' ')
					i++;
			}
		}
		args = malloc(sizeof(char *) * (k + 1));
		if (!args)
			return (NULL);
		i = 0;
		k = 0;
		while (cmd[i])
		{
			if (cmd[i] == '\'')
			{
				i++;
				l = i;
				j = 0;
				while (cmd[i] != 39)
				{
					i++;
					j++;
				}
				args[k] = malloc(sizeof(char) * (j + 1));
				if (!args[k])
					return (NULL);
				j = 0;
			
				while (l < i)
				{
					args[k][j] = cmd[l];
					l++;
					j++;
				}
				args[k][j] = '\0';
				k++;
				i++;
			}
			else if (cmd[i] == '\"')
			{
				i++;
				l = i;
				j = 0;
				while (cmd[i] && cmd[i] != 34)
				{
					i++;
					j++;
				}
				args[k] = malloc(sizeof(char) * (j + 1));
				if (!args[k])
					return (NULL);
				j = 0;
				while (l < i)
				{
					args[k][j] = cmd[l];
					l++;
					j++;
				}
				args[k][j] = '\0';
				k++;
				i++;
			}
			else if (cmd[i] == ' ')
				i++;
			else if (cmd[i] != ' ')
			{
				l = i;
				j = 0;
				while (cmd[i] && cmd[i] != ' ')
				{
					i++;
					j++;
				}
				args[k] = malloc(sizeof(char) * (j + 1));
				if (!args[k])
					return (NULL);
				j = 0;
				while (l < i)
				{
					args[k][j] = cmd[l];
					l++;
					j++;
				}
				args[k][j] = '\0';
				k++;
			}
		}
	}
	return (args);
}

t_cmd	*ft_start_parse(char *cmd_line)
{
	int		i;
	int		j;
	char 	*cmd;
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	t_cmd	*tmp;

	i = 0;
	cmd_list = NULL;
	tmp = NULL;
	while (cmd_line[i])
	{
		j = i;

		// Handle redirection and pipes
		if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
		{
			i += 3;  // Fix: should be i += 2 for '>>'
			while (cmd_line[i] && cmd_line[i] != ' ')
				i++;
			i++;
		}
		else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		{
			i += 3;  // Fix: should be i += 2 for '>>'
			while (cmd_line[i] && cmd_line[i] != ' ')
				i++;
			i++;
		} // Fix: should be i += 2 for '<<'
		else if (cmd_line[i] == '>' || cmd_line[i] == '<')
		{
			i += 2;  // Fix: should be i += 2 for '>>'
			while (cmd_line[i] && cmd_line[i] != ' ')
				i++;
			i++;
		}
		else if (cmd_line[i] == '|')
			i += 2;
		else
		{
			// Regular command until special symbols
			while (cmd_line[i] && cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
				i++;
		}

		// Allocate memory for the command substring
		cmd = malloc(sizeof(char) * (i - j + 1));
		if (!cmd)
			return (NULL); // Error handling
		ft_strlcpy(cmd, &cmd_line[j], i - j + 1);

		// Initialize command structure
		new_cmd = init_cmd();
		if (!new_cmd)
		{
			free(cmd);
			return (NULL); // Error handling
		}
		new_cmd->args = ft_deal_cmd(cmd);
		free(cmd); // Free the temporary command string

		// Add new command to the list
		if (!cmd_list)
			cmd_list = new_cmd;
		else
			tmp->next = new_cmd;

		tmp = new_cmd; // Move tmp to the end of the list
	}

	return (cmd_list);
}

void	ft_print_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		printf("cmd_nbr: %d\n", cmd->cmd_nbr);
		printf("pipe_nbr: %d\n", cmd->pipe_nbr);
		printf("before_pipe: %d\n", cmd->before_pipe);
		printf("after_pipe: %d\n", cmd->after_pipe);
		printf("input: %d\n", cmd->input);
		printf("output: %d\n", cmd->output);
		printf("append: %d\n", cmd->append);
		printf("heredoc: %d\n", cmd->heredoc);
		ft_print_doulbe_pointer(cmd->args);
		cmd = cmd->next;
	}
}
