/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:14:26 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/02 19:16:08 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_token(char *str)
{
	if (!str || !*str)
		return (_null);
	else if (ft_strcmp(str, "|") == 0)
		return (_pipe);
	else if (ft_strcmp(str, "<") == 0)
		return (_redir_in);
	else if (ft_strcmp(str, ">") == 0)
		return (_redir_out);
	else if (ft_strcmp(str, ">>") == 0)
		return (_append);
	else if (ft_strcmp(str, "<<") == 0)
		return (_heredoc);
	return (_word);
}

t_token	**parse_token(const char *input)
{
	size_t		i;
	size_t		j;
	size_t		token_count;
	// t_token		*token;
	t_token		**tokens;

	i = 0;
	token_count = 0;
	tokens = malloc(sizeof(t_token) * (ft_strlen(input) / 2 + 2));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		tokens[token_count] = malloc(sizeof(t_token));
		if (!tokens[token_count])
			return (NULL);
		if (input[i] == '>' && input[i + 1] == '>')
		{
			tokens[token_count]->token = ft_strdup(">>");
			i += 2;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			tokens[token_count]->token = ft_strdup("<<");
			i += 2;
		}
		else if (input[i] == '<')
		{
			tokens[token_count]->token = ft_strdup("<");
			i++;
		}
		else if (input[i] == '>')
		{
			tokens[token_count]->token = ft_strdup(">");
			i++;
		}
		else if (input[i] == '|')
		{
			tokens[token_count]->token = ft_strdup("|");
			i++;
		}
		else
		{
			if (input[i] == '\'' && input[i])
			{
				tokens[token_count]->token = parse_quotes((char *)&input[i]);
				if (tokens[token_count]->token == NULL)
					return (0);
				i += ft_strlen(tokens[token_count]->token) + 2;
			}
			else if (input[i] == '\"' && input[i])
			{
				tokens[token_count]->token = parse_quotes1((char *)&input[i]);
				if (tokens[token_count]->token == NULL)
					return (0);
				i += ft_strlen(tokens[token_count]->token) + 2;
			}
			else
			{
				j = 0;
				while (input[i] != ' ' && input[i] && input[i] != '|' && input[i] != '<' && input[i] != '>' && input[i] != '\'' && input[i] != '\"')
				{
					j++;
					i++;	
				}
				tokens[token_count]->token = ft_strndup(&input[i - j], j);
				
			}
		}
		tokens[token_count]->type = is_token(tokens[token_count]->token);
		token_count++;
	}
	// printf("input: %s\n", tokens[token_count]->token);
	// tokens[token_count]->type = _null;
	// tokens[token_count]->token = NULL;
	tokens[token_count] = NULL;
	return (tokens);
}


void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens == NULL)
		return ;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}