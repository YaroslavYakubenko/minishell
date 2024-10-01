/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_mark.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:29:15 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 15:30:56 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	mark_redirects(t_cmd *start, t_cmd *end, t_cmd *target)
{
	t_cmd	*tmp;

	tmp = start;
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
	mark_redirects(start, end, target);
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
