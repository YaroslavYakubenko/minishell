/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:14:50 by dyao              #+#    #+#             */
/*   Updated: 2024/09/28 14:59:27 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char )*s1 - (unsigned char)*s2);
}

void ft_unset(char *str) {
    int i;
    int count;
    char *temp;
    char *temp2;

    count = 0;
    temp = NULL;
    temp2 = NULL;
    i = open("index", O_RDWR);
    if (i < 0)
        return;
    temp = get_next_line(i);
    while (temp)
	{
        if (ft_strcmp(temp, str) == 0 || ft_strcmp(temp, str) == 61 || ft_strcmp(temp, str) == 10)
			;
        else if (count++ == 0)
            temp2 = ft_strdup(temp);
        else
            temp2 = ft_strjoin(temp2, temp);
        free(temp);
        temp = get_next_line(i);
    }
    close(i);
    i = open("index", O_RDWR | O_TRUNC);
    if (i < 0)
	{
        free(temp2);
        return;
    }
	if (temp2)
    	write(i, temp2, ft_strlen(temp2));
    close(i);
    free(temp2);
}

int	ft_check_equal_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && (str[i + 1] == '\'' || str[i + 1] == '\"') && (str[i + 2] != '\'' && str[i + 2] != '\"'))
			return (5);//有引号有内容
		else if (str[i] == '=' && (str[i + 1] == '\'' || str[i + 1] == '\"') && (str[i + 2] == '\'' || str[i + 2] == '\"'))
			return (4);//有引号没内容
		else if (str[i] == '=' && str[i + 1] && (str[i + 1] != '\'' || str[i + 1] != '\"'))
			return (3);//有内容但是不确定内容里其他位置有没有引号
		else if (str[i] == '=' && !str[i + 1])
			return (2);//没有内容但有等号
		i++;
	}
	return (1);//没有内容也没有等号，但是可能会有引号
}

char	*ft_deal_record_v5(char *str)
{
	int		i;
	int		j;
	char	*output;

	i = ft_strlen(str);
	output = malloc((i - 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (output);
}

char	*ft_deal_record_v4(char *str)
{
	char	*output;
	int		i;

	if (ft_strchr(str, '\"'))
	{
		output = ft_strdup(str);
		i = ft_strlen(str);
		output[i - 1] = '\'';
		output[i - 2] = '\'';
		return (output);
	}
	else
		return (ft_strdup(str));
}

char	*ft_deal_record_v3(char *str)
{
	char	*output;
	int		i;
	int		j;

	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
	{
		i = ft_strlen(str);
		output = malloc((i - 1) * sizeof(char));
		if (!output)
			return (NULL);
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i++;
			else
				output[j++] = str[i++];
		}
		output[j] = '\0';
		return (output);
	}
	else
		return (ft_strdup(str));
}

char	*ft_deal_record_v2(char *str)
{
	char	*output;
	int		i;

	i = ft_strlen(str);
	output = malloc((i + 3) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = '\'';
	output[i++] = '\'';
	output[i] = '\0';
	return (output);
}

char	*ft_deal_record(int mark, char *str)
{
	if (mark == 5)
		return (ft_deal_record_v5(str));
	else if (mark == 4)
		return (ft_deal_record_v4(str));
	else if (mark == 3)
		return (ft_deal_record_v3(str));
	else if (mark == 2)
		return (ft_deal_record_v2(str));
	else
		return (ft_strdup(str));
}

char	*ft_delete_quote_before_equal(char *str)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (str[j] && str[j] != '\'' && str[j] != '\"')
		j++;
	if (j >= i)
		return (ft_strdup(str));
	i = ft_strlen(str);
	output = malloc((i - 1) * sizeof(char));
	if (!output)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
			output[j++] = str[i++];
	}
	while (str[i])
		output[j++] = str[i++];
	output[j] = '\0';
	return (output);
}

int	ft_compare_strs(char *temp, char *final)
{
	int	i;

	i = 0;
	if (!ft_strcmp(temp, final) || ft_strcmp(temp, final) == 10 || ft_strcmp(temp, final) == -51)
		return (1);
	while (temp[i] && final[i])
	{
		if (temp[i] == final[i] && temp[i] == '=')
			return (1);
		else if (temp[i] == final[i])
			i++;
		else
			return(0);
	}
	if (final[i] == '=')
		return (1);
	return (0);
}

int	ft_renew_list(char *final)
{
	int 	i;
    int 	count;
	int		mark;
    char	*temp;
    char	*temp2;

    count = 0;
	mark = 0;
    temp = NULL;
    temp2 = NULL;
    i = open("index", O_RDWR);
    if (i < 0)
        return (0);
    temp = get_next_line(i);
    while (temp)
	{
        if (ft_compare_strs(temp, final) == 1)
		{
			free(temp);
			temp = ft_strjoin(final, "\n");
			mark = 1;
		}
        if (count++ == 0)
            temp2 = ft_strdup(temp);
        else
            temp2 = ft_strjoin(temp2, temp);
        free(temp);
        temp = get_next_line(i);
    }
    close(i);
    i = open("index", O_RDWR | O_TRUNC);
    if (i < 0)
	{
        free(temp2);
        return (0);
    }
	if (temp2)
    	write(i, temp2, ft_strlen(temp2));
    close(i);
    free(temp2);
	return (mark);
}

void	ft_record(char *str)
{
	int		j;
	int		mark;
	char	*temp;
	char	*final;

	
	temp = ft_delete_quote_before_equal(str);
	mark = ft_check_equal_quote(str);
	final = ft_deal_record(mark, temp);
	free(temp);
	if (ft_renew_list(final) != 1)
	{
		j = open("index", O_RDWR | O_CREAT | O_APPEND, 0777);
		write(j, final, ft_strlen(final));
		write(j, "\n", 1);
	}
	free(final);
}

void	ft_read_and_print(void)
{
	int		fd;
	int		i;
	char	*temp;

	fd = open("index", O_RDONLY);
	if (fd < 0)
		return ;
	temp = get_next_line(fd);
	if (!temp)
		return ;
	while (temp)
	{
		i = 0;
		while (temp[i])
		{
			if (temp[i] == '=')
				printf("%s", temp);
			i++;
		}
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}
