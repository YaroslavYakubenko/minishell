/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:54:41 by dyao              #+#    #+#             */
/*   Updated: 2024/09/30 17:32:31 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_and_execute(char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0)
		ft_export(cmd, envp);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		;
	else
		ft_execute(cmd, envp);
}

int	**ft_creat_pipe(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;
	int		**pipes;

	i = 0;
	temp = cmd;
	while (temp)
	{
		if (temp->pipe_nbr)
			i++;
		temp = temp->next;
	}
	if (!i)
		return (NULL);
	pipes = malloc((i + 1) * sizeof(int *));
	if (!pipes)
		return (NULL);
	pipes[i] = NULL;
	while (i > 0)
	{
		pipes[i - 1] = malloc(2 * sizeof(int));
		pipe(pipes[i - 1]);
		i--;
	}
	return (pipes);
}

pid_t	*ft_creat_pids(t_cmd *cmd)
{
	t_cmd	*temp;
	pid_t	*pids;
	int		i;

	i = 0;
	temp = cmd;
	while (temp)
	{
		if (temp->cmd_nbr)
			i++;
		temp = temp->next;
	}
	pids = ft_calloc(i + 1, sizeof(pid_t));
	if (!pids)
		return (NULL);
	pids[i] = 0;
	return (pids);
}

void	ft_free_double_pointer_int(int **pointer)
{
	int	i;

	i = 0;
	if (!pointer)
		return ;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

int	ft_break_condition(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->cmd_nbr)
			i = 1;
		cmd = cmd->next;
	}
	return (i);
}

void print_from_fd(int fd)
{
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
	{
		if (bytesRead == -1)
			perror("read failed");
        if (write(STDOUT_FILENO, buffer, bytesRead) == -1)
		{
            perror("write failed");
            exit(EXIT_FAILURE);
        }
    }
	close(fd);
}

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
				ft_wait_pid(pid, 0);
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
	if (temp->output)
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
				ft_wait_pid(pid, 0);
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

void	handle_parent_pipes(t_cmd *temp, int **pipes, int *i_for_pipe)
{
	if (temp->after_pipe)
	{
		close(pipes[*i_for_pipe][0]);
		(*i_for_pipe)++;
	}
	if (temp->before_pipe)
	{
		close(pipes[*i_for_pipe][1]);
	}
}

void	wait_for_pids(pid_t *pids)
{
	int i_for_pid;

	i_for_pid = 0;
	while (pids[i_for_pid])
	{
		ft_wait_pid(pids[i_for_pid], i_for_pid);
		i_for_pid++;
	}
}

void	ft_run_cmd(t_cmd *cmd, int **pipes, pid_t *pids, char **evnp)
{
	t_cmd	*search;
	t_cmd	*start;
	t_cmd	*temp;
	int		i_for_pid;
	int		i_for_pipe;
	int		mark;

	search = cmd;
	temp = cmd;
	start = cmd;
	i_for_pid = 0;
	i_for_pipe = 0;
	while (temp)
	{
		mark = 0;
		while (temp->next && !temp->cmd_nbr)
			temp = temp->next;
		if (strcmp(cmd->args[0], "cd") == 0)
			ft_cd(cmd->args[1]);
		pids[i_for_pid] = fork();
		if (pids[i_for_pid] == -1)
			perror(strerror(errno));
		if (pids[i_for_pid] == 0)
		{
			handle_heredoc(temp, search, start);
			handle_input(temp, search, start);
			handle_pipes(temp, pipes, &i_for_pipe);
			mark = handle_append(temp, search, start);
			mark = handle_output(temp, search, start);
			if (mark == 0)
				ft_check_and_execute(temp->args, evnp);
			exit(EXIT_SUCCESS);
		}
		ft_wait_pid(pids[i_for_pid], i_for_pid);
		handle_parent_pipes(temp, pipes, &i_for_pipe);
		while (temp->next && !temp->pipe_nbr)
			temp = temp->next;
		start = temp->next;
		if (!temp->next)
    		break ;
		i_for_pid++;
	}
	// wait_for_pids(pids);
	ft_free_double_pointer_int(pipes);
}

// void	ft_run_cmd(t_cmd *cmd, int **pipes, pid_t *pids, char **evnp)
// {
// 	t_cmd	*search;
// 	t_cmd	*start;
// 	t_cmd	*temp;
// 	int		i_for_pid;
// 	int		i_for_pipe;

// 	search = cmd;
// 	temp = cmd;
// 	start = cmd;
// 	i_for_pid = 0;
// 	i_for_pipe = 0;
// 	while (temp)
// 	{
// 		while (temp->next && !temp->cmd_nbr)
// 			temp = temp->next;
// 		if (strcmp(cmd->args[0], "cd") == 0)
// 			ft_cd(cmd->args[1]);
// 		pids[i_for_pid] = fork();
// 		if (pids[i_for_pid] == -1)
// 			perror(strerror(errno));
// 		if (pids[i_for_pid] == 0)
// 		{
// 			if (temp->heredoc)
// 			{
// 				while (search)
// 				{
// 					if (search->heredoc && !search->cmd_nbr)
// 						break ;
// 					search = search->next;
// 				}
// 				ft_heredocs(search->args[1]);
// 				search = start;
// 			}								//something wrong with the heredoc, not decided yet
// 			if (temp->input)
// 			{
// 				while (search)
// 				{
// 					if (search->input && !search->cmd_nbr)
// 						break ;
// 					search = search->next;
// 				}
// 				ft_input(search->args[1]);
// 				search = start;
// 			}
// 			if (temp->output)
// 			{
// 				while (search)
// 				{
// 					if (search->output && !search->cmd_nbr)
// 						break ;
// 					search = search->next;
// 				}
// 				ft_output(search->args[1]);
// 				search = start;
// 			}
// 			if (temp->append)
// 			{
// 				while (search)
// 				{
// 					if (search->append && !search->cmd_nbr)
// 						break ;
// 					search = search->next;
// 				}
// 				ft_append(search->args[1]);
// 				search = start;
// 			}
// 			if (temp->after_pipe)
// 			{
// 				dup2(pipes[i_for_pipe][0], STDIN_FILENO);
// 				close(pipes[i_for_pipe][1]);
// 				close(pipes[i_for_pipe][0]);
// 				i_for_pipe++;
// 			}
// 			if (temp->before_pipe)
// 			{
// 				dup2(pipes[i_for_pipe][1], STDOUT_FILENO);
// 				close(pipes[i_for_pipe][0]);
// 				close(pipes[i_for_pipe][1]);
// 			}
// 			ft_check_and_execute(temp->args, evnp);
// 			exit(EXIT_SUCCESS);
// 		}
// 		if (temp->after_pipe)
// 		{
// 			close(pipes[i_for_pipe][0]);
// 			i_for_pipe++;
// 		}
// 		if (temp->before_pipe)
// 		{
// 			close(pipes[i_for_pipe][1]);
// 		}
// 		while (temp->next && !temp->pipe_nbr)
// 			temp = temp->next;
// 		start = temp->next;
// 		if (!temp->next)
//     		break ;
// 		i_for_pid++;
// 	}
// 	i_for_pid = 0;
// 	while (pids[i_for_pid])
// 	{
// 		ft_wait_pid(pids[i_for_pid], i_for_pid);
// 		i_for_pid++;
// 	}
// 	ft_free_double_pointer_int(pipes);
// 	free(pids);
// }

void	ft_free_nods(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		i = 0;
		temp = cmd->next;
		while(cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		free(cmd);
		cmd = temp;
	}
}

void	ft_start(t_cmd *cmd, char **evnp)
{
	int		**pipe;
	pid_t	*pids;

	if (!cmd)
		return ;
	if (strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd);
	pipe = ft_creat_pipe(cmd);
	pids = ft_creat_pids(cmd);
	ft_run_cmd(cmd, pipe, pids, evnp);
	ft_free_nods(cmd);
	free(pids);
}
