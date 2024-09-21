/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:54:41 by dyao              #+#    #+#             */
/*   Updated: 2024/09/22 00:18:35 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_and_execute(char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0)
		ft_export(cmd, envp);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd[1]);
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
	pipes = malloc(i * sizeof(int *));
	if (!pipes)
		return (NULL);
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
	pids = malloc(i * sizeof(pid_t));
	if (!pids)
		return (NULL);
	return (pids);
}

void	ft_free_double_pointer(int **pointer)
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

void print_from_fd(int fd) {
    char buffer[1024];
    ssize_t bytesRead;

    // Read from the file descriptor in a loop
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        // Write the read bytes to STDOUT
        if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("read failed");
    }
	close(fd);
}


void	ft_run_cmd(t_cmd *cmd, int **pipes, pid_t *pids, char **evnp)
{
	t_cmd	*search;
	t_cmd	*start;
	t_cmd	*temp;
	int		i_for_pid;
	int		i_for_pipe;

	search = cmd;
	temp = cmd;
	start = cmd;
	i_for_pid = 0;
	i_for_pipe = 0;
	while (temp)
	{
		fprintf(stderr, "test1\n");
		while (temp->next && !temp->cmd_nbr)
			temp = temp->next;
		fprintf(stderr, "test2\n");
		pids[i_for_pid] = fork();
		if (pids[i_for_pid] == -1)
			perror(strerror(errno));
		fprintf(stderr, "test3\n");
		fprintf(stderr, "the pid is: %d\n", pids[i_for_pid]);
		if (pids[i_for_pid] == 0)
		{
		fprintf(stderr, "test4\n");
			if (temp->heredoc)
			{
				fprintf(stderr, "test5\n");
				while (search)
				{
					if (search->heredoc && !search->cmd_nbr)
						break ;
					search = search->next;
				}
				fprintf(stderr, "test6\n");
				ft_heredocs(search->args[1]);
				search = start;
			}								//something wrong with the heredoc, not decided yet
			if (temp->input)
			{
				fprintf(stderr, "test7\n");
				while (search)
				{
					if (search->input && !search->cmd_nbr)
						break ;
					search = search->next;
				}
				fprintf(stderr, "test8\n");
				ft_input(search->args[1]);
				search = start;
			}
			if (temp->output)
			{
				fprintf(stderr, "test9\n");
				while (search)
				{
					if (search->output && !search->cmd_nbr)
						break ;
					search = search->next;
				}
				fprintf(stderr, "test10\n");
				ft_output(search->args[1]);
				search = start;
			}
			if (temp->append)
			{
				fprintf(stderr, "test11\n");
				while (search)
				{
					if (search->append && !search->cmd_nbr)
						break ;
					search = search->next;
				}
				fprintf(stderr, "test12\n");
				ft_append(search->args[1]);
				search = start;
			}
			if (temp->after_pipe)
			{
				fprintf(stderr, "test13\n");
				dup2(pipes[i_for_pipe][0], STDIN_FILENO);
				fprintf(stderr, "test14\n");
				close(pipes[i_for_pipe][0]);
				close(pipes[i_for_pipe][1]);
				// fprintf(stderr, "this is pipes:\n");
				// print_from_fd(pipes[i_for_pipe][0]);
				// fprintf(stderr, "this is input:\n");
				// print_from_fd(STDIN_FILENO);
				fprintf(stderr, "test15\n");
				i_for_pipe++;
				// exit(EXIT_SUCCESS);
			}
			if (temp->before_pipe)
			{
				fprintf(stderr, "test16\n");
				dup2(pipes[i_for_pipe][1], STDOUT_FILENO);
				fprintf(stderr, "test17\n");
				close(pipes[i_for_pipe][0]);
				close(pipes[i_for_pipe][1]);
				fprintf(stderr, "test18\n");
			}
			fprintf(stderr, "test19\n");
			ft_check_and_execute(temp->args, evnp);
			fprintf(stderr, "test20\n");
			exit(EXIT_SUCCESS);
		}
		fprintf(stderr, "parent is waiting!\n");
		ft_wait_pid(pids[i_for_pid], i_for_pid);
		fprintf(stderr, "parent, test21\n");
		while (temp->next && !temp->pipe_nbr)
			temp = temp->next;
		fprintf(stderr, "test22\n");
		start = temp->next;
		if (!temp->next)
    		break ;
		i_for_pid++;
	}
	i_for_pid = 0;
	fprintf(stderr, "test23\n");
	fprintf(stderr, "test23\n");
	fprintf(stderr, "test23\n");
	while (pids[i_for_pid])
	{
	fprintf(stderr, "test23.5\n");
		// free(pids[i_for_pid]);
		i_for_pid++;
	}
	fprintf(stderr, "test24\n");
	ft_free_double_pointer((int **)pipes);
	fprintf(stderr, "test25\n");
}

void	ft_start(t_cmd *cmd, char **evnp)
{
	int		**pipe;
	pid_t	*pids;

	pipe = ft_creat_pipe(cmd);
	pids = ft_creat_pids(cmd);
	ft_run_cmd(cmd, pipe, pids, evnp);
}
