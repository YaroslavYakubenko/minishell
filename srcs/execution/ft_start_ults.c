/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_ults.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:16:53 by dyao              #+#    #+#             */
/*   Updated: 2024/10/03 18:35:07 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_cmd *temp, t_cmd *search, t_cmd *start)
{
	search = start;
	if (temp->heredoc)
	{
		while (search)
		{
			if (search->heredoc && !search->cmd_nbr)
				break ;
			search = search->next;
		}
		ft_heredocs(search->args[1]);
		search = start;
	}
}

void	handle_input(t_cmd *temp, t_cmd *search, t_cmd *start)
{
	search = start;
	if (temp->input)
	{
		while (search)
		{
			if (search->input && !search->cmd_nbr)
				break ;
			search = search->next;
		}
		ft_input(search->args[1]);
		search = start;
	}
}

int	handle_output(t_cmd *temp, t_cmd *search, t_cmd *start)
{
	pid_t	pid;
	int		mark;

	mark = 0;
	search = start;
	if (temp->output)
	{
		while (search)
		{
			if (search->output && !search->cmd_nbr)
			{
				pid = fork();
				if (pid == 0)
				{
					ft_output(search->args[1]);
					ft_check_and_execute(temp->args, temp->evnp);
				}
				waitpid(pid, NULL, 0);
			}
			search = search->next;
		}
		search = start;
		mark = 1;
	}
	return (mark);
}

int	handle_append(t_cmd *temp, t_cmd *search, t_cmd *start)
{
	pid_t	pid;
	int		mark;

	mark = 0;
	search = start;
	if (temp->append)
	{
		while (search)
		{
			if (search->append && !search->cmd_nbr)
			{
				pid = fork();
				if (pid == 0)
				{
					ft_append(search->args[1]);
					ft_check_and_execute(temp->args, temp->evnp);
				}
				waitpid(pid, NULL, 0);
			}
			search = search->next;
		}
		search = start;
		mark = 1;
	}
	return (mark);
}

void	handle_pipes(t_cmd *temp, int **pipes, int *i_for_pipe)
{
	if (temp->after_pipe)
	{
		dup2(pipes[*i_for_pipe][0], STDIN_FILENO);
		close(pipes[*i_for_pipe][1]);
		close(pipes[*i_for_pipe][0]);
		(*i_for_pipe)++;
	}
	if (temp->before_pipe)
	{
		dup2(pipes[*i_for_pipe][1], STDOUT_FILENO);
		close(pipes[*i_for_pipe][0]);
		close(pipes[*i_for_pipe][1]);
	}
}
