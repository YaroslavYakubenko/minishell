/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:07:58 by dyao              #+#    #+#             */
/*   Updated: 2024/09/28 14:56:37 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_output_single_evnp(char *evnp)
{
	int		i;
	char	*output_evnp;
	char	*new_evnp;

	i = 0;
	while (evnp[i] && evnp[i] != '=')
		i++;
	new_evnp = malloc((i + 1) * sizeof(char));
	i = 0;
	while (evnp[i] && evnp[i] != '=')
	{
		new_evnp[i] = evnp[i];
		i++;
	}
	new_evnp[i] = '\0';
	output_evnp = getenv(new_evnp);
	new_evnp = ft_strjoin_1(new_evnp, "=");
	new_evnp = ft_strjoin_1(new_evnp, output_evnp);
	return (new_evnp);
}

char	**ft_renew_evnp(char **evnp)
{
	int		i;
	int		j;
	char	**new_evnp;
	char	*single_evnp;

	i = 0;
	while (evnp[i])
		i++;
	new_evnp = malloc((i + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (evnp[i])
	{
		single_evnp = ft_output_single_evnp(evnp[i]);
		new_evnp[i] = single_evnp;
		i++;
	}
	new_evnp[i] = NULL;
	return (new_evnp);
}

char	**ft_sort_the_evnp(char **store)
{
	char	*temp;
	int		i;

	i = 0;
	while (store[i + 1] != NULL)
	{
		if (ft_strcmp(store[i], store[i + 1]) > 0)
		{
			temp = store[i];
			store[i] = store[i + 1];
			store[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (store);
}

void	ft_print_double_pointer(char **str)
{
	int	i;

	if (!str || !str[0])
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '_')
			printf("%s\n", str[i]);
		i++;
	}
}

char	**ft_add_list(char **store)
{
	int		fd;
	int		i;
	int		j;
	char	*temp;
	char	**output;

	fd = open("index", O_RDONLY);
	if (fd < 0)
		return (store);
	i = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		i++;
		temp = get_next_line(fd);
	}
	close(fd);
	fd = 0;
	while (store[fd])
		fd++;
	output = malloc((i + fd + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	i = 0;
	while (store[i])
	{
		output[i] = store[i];
		i++;
	}
	fd = open("index", O_RDONLY);
	temp = get_next_line(fd);
	while (temp)
	{
		j = 0;
		while (temp[j] != '\n' && temp[j])
			j++;
		temp[j] = '\0';
		output[i++] = temp;
		temp = get_next_line(fd);
	}
	output[i] = NULL;
	free(store);
	return (output);
}

void	ft_print_env(char **evnp)
{
	char	**store;

	store = ft_renew_evnp(evnp);
	ft_print_double_pointer(store);
	ft_read_and_print();
}

void	ft_export(char	**argv, char **evnp)
{
	char	**store;
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1 && ft_strcmp(argv[0], "export") == 0)
	{
		store = ft_renew_evnp(evnp);
		store = ft_add_list(store);
		store = ft_sort_the_evnp(store);
		ft_print_double_pointer(store);
	}
	else if (argc == 1 && ft_strcmp(argv[0], "env") == 0)
		ft_print_env(evnp);
	else if (argc > 1 && ft_strcmp(argv[0], "export") == 0)
		ft_record(argv[1]);
	else if (argc == 1 && ft_strcmp(argv[0], "unset") == 0)
		printf("unset: not enough arguments\n");
	else if (argc > 1 && ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argv[1]);
}
