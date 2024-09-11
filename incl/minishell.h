/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:02:53 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/11 22:25:03 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
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

typedef struct s_cmd
{
	char			**args;	// An array of command arguments["ls", "-l", NULL]
	char			*in_rd;	// Input redirection file, e.g., "input.txt"
	char			*out_rd;// Output redirection file, e.g., "output.txt"
	int				append;	// Flag for append mode (1 for >>, 0 for >)
	int				heredoc;
	struct s_cmd	*next;	// Pointer to the next command in case of pipes
}	t_cmd;

// Parse
t_env	*create_env_node(char *env_str);
t_env	*init_new_list(char **envp);
char	*get_env_val(const char *name, t_env *env);
char	*replace_var_with_value(const char *input, const char *pos, char *value, size_t var_len);
char	*expand_env_variables(const char *input, t_env *env);
t_token	**init_token(size_t len);
int		is_token(char *str);
int		parse_special_token(const char *input, size_t *i, t_token **tokens, size_t *token_count);
int		parse_qoutes_token(const char *input, size_t *i, t_token **tokens, size_t *token_count);
void	parse_word_token(const char *input, size_t *i, t_token **tokens, size_t *token_count);
t_token	**parse_token(const char *input);
void	free_tokens(char **tokens);
char	*parse_single_quotes(char *input);
char	*parse_double_quotes(char *input);
char	*append_var_to_result(char *result, const char *pos, size_t len);
size_t	extract_var_name(const char *pos, char *var_name);
void	check_quotes(char c, int *in_single_quote, int *in_double_quote);
char	*process_variable(char *result, char *pos, t_env *env, int in_single_quote);
char	*create_new_str(const char *input, size_t var_len, const char *pos);
char	*update_position(char *result, char *new_result, char *pos);
char	*compress_spaces(char *input);
char	*expand_and_compress(char *input, t_env *env);
int	check_pipe_error(const char *input, size_t i);
int	check_redirect_error(const char *input, size_t i);

// Execution
void	ft_execute(char **cmd, char **envp);
char	*ft_get_evn(char **envp, char *keyword, char *cmd);
void	ft_input(char *file_name);
void	ft_output(char *file_name);
void	ft_append(char *file_name);
void	ft_heredocs(char *end);
void	ft_pipe(void);
void	ft_export(char	**argv, char **evnp);
void	ft_cd(char *dest_dir);
int		ft_unset(char **record, char *str, int j);
char	*ft_record(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_build_in(char **cmd, char **envp);
void	ft_start(t_token **tokens, char **evnp);
void	ft_put_null(char **record);
void	ft_wait_pid(pid_t pid_first);

// Utils
size_t	ft_strlenn(const char *str);
char	*allocate_new_input(size_t len);

#endif