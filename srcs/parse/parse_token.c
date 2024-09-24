/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:14:26 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/24 20:51:37 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**init_token(size_t len)
{
	t_token	**tokens;

	tokens = malloc(sizeof(t_token *) * (len / 2 + 2));
	if (!tokens)
		return (NULL);
	return (tokens);
}

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

int	parse_special_token(const char *input, size_t *i, t_token **tokens, size_t *token_count)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		tokens[*token_count]->token = ft_strdup(">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		tokens[*token_count]->token = ft_strdup("<<");
		*i += 2;
	}
	else if (input[*i] == '<')
	{
		tokens[*token_count]->token = ft_strdup("<");
		*i += 1;
	}
	else if (input[*i] == '>')
	{
		tokens[*token_count]->token = ft_strdup(">");
		*i += 1;
	}
	else if (input[*i] == '|')
	{
		tokens[*token_count]->token = ft_strdup("|");
		*i += 1;
	}
	else
		return (0);
	tokens[*token_count]->type = is_token(tokens[*token_count]->token);
	*token_count += 1;
	return (1);
}

int	parse_qoutes_token(const char *input, size_t *i, t_token **tokens, size_t *token_count)
{
	if (input[*i] == '\'' && input[*i])
	{
		tokens[*token_count]->token = parse_single_quotes((char *)&input[*i]);
		if (!tokens[*token_count]->token)
			return (0);
		*i += ft_strlen(tokens[*token_count]->token) + 2;
	}
	else if (input[*i] == '\"' && input[*i])
	{
		tokens[*token_count]->token = parse_double_quotes((char *)&input[*i]);
		if (!tokens[*token_count]->token)
			return (0);
		*i += ft_strlen(tokens[*token_count]->token) + 2;
	}
	else
		return (0);
	tokens[*token_count]->type = is_token(tokens[*token_count]->token);
	*token_count += 1;
	return (1);
}

void	parse_word_token(const char *input, size_t *i, t_token **tokens, size_t *token_count)
{
	size_t	j;

	j = 0;
	while (input[*i] != ' ' && input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '\'' && input[*i] != '\"')
	{
		j++;
		*i += 1;
	}
	tokens[*token_count]->token = ft_strndup(&input[*i - j], j);
	tokens[*token_count]->type = is_token(tokens[*token_count]->token);
	*token_count += 1;
}

t_token	**parse_token(const char *input)
{
	size_t		i;
	size_t		token_count;
	t_token		**tokens;

	i = 0;
	token_count = 0;
	tokens = init_token(ft_strlen(input));
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
		if (input[i] == '|')
		{
			if (check_pipe_error(input, i))
			{
				printf("Syntax error: Invalid pipe usage\n");
				free(tokens[token_count]);
				return (NULL);
			}
		}
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		{
			if (check_redirect_error(input, i))
			{
				printf("Syntax error: Invalid redirection usage\n");
				free(tokens[token_count]);
				return (NULL);
			}
		}
		if (parse_special_token(input, &i, tokens, &token_count))
			continue ;
		if (parse_qoutes_token(input, &i, tokens, &token_count))
			continue ;
		parse_word_token(input, &i, tokens, &token_count);
	}
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
