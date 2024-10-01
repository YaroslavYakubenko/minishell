/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_ults_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:21:56 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 15:06:59 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_in_child(t_cmd *temp, t_cmd *start, int **pipes, int *i_for_pipe)
{
	t_cmd	*search;
	int		mark;

	mark = 0;
	search = start;
	handle_heredoc(temp, search, start);
	handle_input(temp, search, start);
	handle_pipes(temp, pipes, i_for_pipe);
	mark = handle_append(temp, search, start);
	mark = handle_output(temp, search, start);
	if (mark == 0)
		ft_check_and_execute(temp->args, temp->evnp);
	exit(EXIT_SUCCESS);
}

t_cmd	*find_next_command(t_cmd *temp)
{
	while (temp->next && !temp->cmd_nbr)
		temp = temp->next;
	return (temp);
}

t_cmd	*find_next_pipe(t_cmd *temp)
{
	while (temp->next && !temp->pipe_nbr)
		temp = temp->next;
	return (temp);
}

void	ft_check_cd(t_cmd *cmd)
{
	if (strcmp(cmd->args[0], "cd") == 0)
		ft_cd(cmd->args[1]);
	else
		return ;
}

void	ft_run_cmd(t_cmd *cmd, int **pipes, pid_t *pids)
{
	t_cmd	*start;
	t_cmd	*temp;
	int		i_for_pid;
	int		i_for_pipe;

	temp = cmd;
	start = cmd;
	i_for_pid = 0;
	i_for_pipe = 0;
	while (temp)
	{
		temp = find_next_command(temp);
		ft_check_cd(temp);
		pids[i_for_pid] = fork();
		if (pids[i_for_pid] == 0)
			ft_in_child(temp, start, pipes, &i_for_pipe);
		ft_wait_pid(pids[i_for_pid], i_for_pid);
		handle_parent_pipes(temp, pipes, &i_for_pipe);
		temp = find_next_pipe(temp);
		start = temp->next;
		if (!temp->next)
			break ;
		i_for_pid++;
	}
	ft_free_double_pointer_int(pipes);
}

// void	ft_run_cmd(t_cmd *cmd, int **pipes, pid_t *pids)
// {
// 	t_cmd	*search;
// 	t_cmd	*start;
// 	t_cmd	*temp;
// 	int		i_for_pid;
// 	int		i_for_pipe;
// 	int		mark;

// 	search = cmd;
// 	temp = cmd;
// 	start = cmd;
// 	i_for_pid = 0;
// 	i_for_pipe = 0;
// 	while (temp)
// 	{
// 		mark = 0;
// 		while (temp->next && !temp->cmd_nbr)
// 			temp = temp->next;
// 		if (strcmp(cmd->args[0], "cd") == 0)
// 			ft_cd(cmd->args[1]);
// 		pids[i_for_pid] = fork();
// 		if (pids[i_for_pid] == -1)
// 			perror(strerror(errno));
// 		if (pids[i_for_pid] == 0)
// 		{
// 			handle_heredoc(temp, search, start);
// 			handle_input(temp, search, start);
// 			handle_pipes(temp, pipes, &i_for_pipe);
// 			mark = handle_append(temp, search, start);
// 			mark = handle_output(temp, search, start);
// 			if (mark == 0)
// 				ft_check_and_execute(temp->args, temp->evnp);
// 			exit(EXIT_SUCCESS);
// 		}
// 		ft_wait_pid(pids[i_for_pid], i_for_pid);
// 		handle_parent_pipes(temp, pipes, &i_for_pipe);
// 		while (temp->next && !temp->pipe_nbr)
// 			temp = temp->next;
// 		start = temp->next;
// 		if (!temp->next)
// 			break ;
// 		i_for_pid++;
// 	}
// 	ft_free_double_pointer_int(pipes);
// }
