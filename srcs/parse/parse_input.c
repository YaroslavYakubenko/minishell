/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:40:27 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/27 16:27:15 by yyakuben         ###   ########.fr       */
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

int	ft_get_parts(char *cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
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
	return (k);
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
		k = ft_get_parts(cmd);
		args = malloc(sizeof(char *) * (k + 1));
		if (!args)
			return (NULL);
		while (k >= 0)
		{
			args[k] = NULL;
			k--;
		}
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

int	ft_find_end(char *cmd_line, int i)
{
	if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
	{
		i += 3;
		while (cmd_line[i] && cmd_line[i] != ' ')
			i++;
		i++;
	}
	else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
	{
		i += 3;
		while (cmd_line[i] && cmd_line[i] != ' ')
			i++;
		i++;
	}
	else if (cmd_line[i] == '>' || cmd_line[i] == '<')
	{
		i += 2;
		while (cmd_line[i] && cmd_line[i] != ' ')
			i++;
		i++;
	}
	else if (cmd_line[i] == '|')
		i += 2;
	else
	{
		while (cmd_line[i] && cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
			i++;
	}
	return (i);
}

t_cmd	*ft_start_parse(char *cmd_line, char **evnp)
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
	while (i <= (int)ft_strlen(cmd_line) && cmd_line[i])
	{
		j = i;
		i = ft_find_end(cmd_line, i);
		cmd = malloc(sizeof(char) * (i - j + 1));
		if (!cmd)
			return (NULL);
		ft_strlcpy(cmd, &cmd_line[j], i - j + 1);
		new_cmd = init_cmd(evnp);
		if (!new_cmd)
		{
			free(cmd);
			return (NULL);
		}
		free(new_cmd->args);
		new_cmd->args = ft_deal_cmd(cmd);
		free(cmd);
		if (!cmd_list)
			cmd_list = new_cmd;
		else
			tmp->next = new_cmd;
		tmp = new_cmd;
	}
	free(cmd_line);
	return (cmd_list);
}

void	ft_give_marks(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->args[0][0] == '<' && tmp->args[0][1] == '<')
			tmp->heredoc = 1;
		else if (tmp->args[0][0] == '>' && tmp->args[0][1] == '>')
			tmp->append = 1;
		else if (tmp->args[0][0] == '>')
			tmp->output = 1;
		else if (tmp->args[0][0] == '<')
			tmp->input = 1;
		else if (tmp->args[0][0] == '|')
			tmp->pipe_nbr = 1;
		else
			tmp->cmd_nbr = 1;
		tmp = tmp->next;
	}
}

int	ft_check_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
	{
		if (tmp->next->pipe_nbr)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_cmd	*ft_handle_cmd_mark_v2(t_cmd *start, t_cmd *target)
{
	t_cmd	*end;
	t_cmd	*tmp;

	if (start == target)
		tmp = start;
	else
		tmp = start->next;
	while (tmp->next && !tmp->pipe_nbr)
		tmp = tmp->next;
	end = tmp;
	tmp = start;
	if (end->pipe_nbr)
		target->before_pipe = 1;
	if (start->pipe_nbr)
		target->after_pipe = 1;
	while (tmp && tmp != end->next)
	{
		if (tmp->input == 1)
			target->input = 1;
		else if (tmp->output == 1)
			target->output = 1;
		else if (tmp->append == 1)
			target->append = 1;
		else if (tmp->heredoc == 1)
			target->heredoc = 1;
		tmp = tmp->next;
	}
	return (end);
}

void	ft_handle_cmd_mark(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*end_start;

	tmp = cmd;
	end_start = cmd;
	while (tmp)
	{
		if (tmp->cmd_nbr)
			end_start = ft_handle_cmd_mark_v2(end_start, tmp);
		tmp = tmp->next;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd)
	{
		printf("this is the %d command: \n", i);
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
		i++;
	}
}
