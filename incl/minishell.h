/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:02:53 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/25 21:06:33 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>  
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>

# define MAX_TOKENS 100

typedef struct s_mshell
{
	// t_env *env;
	int	   exit_code;
} t_mshell;

typedef enum e_token_type
{
	_word,
	_pipe,
	_redir_in,
	_redir_out,
	_append,
	_heredoc,
	_null,
}	t_token_type;

typedef struct s_token
{
	char		*token;
	t_token_type	type;
}	t_token;

typedef struct s_env
{
	char	*name;
	char	*val;
	struct s_env	*next;
}	t_env;

t_env	*create_env_node(char *env_str);
t_env	*init_new_list(char **envp);
char	*get_env_val(const char *name, t_env *env);
char	*replace_var_with_value(const char *input, const char *pos, t_env *env);
char	*expand_env_variables(const char *input, t_env *env);
int		is_token(char *str);
t_token	**parse_token(const char *input);
void	free_tokens(char **tokens);

// Utils
size_t	ft_strlenn(const char *str);

#endif