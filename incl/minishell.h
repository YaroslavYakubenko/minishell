/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:02:53 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/04 22:13:26 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
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
	int	exit_code;
}	t_mshell;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	int				cmd_nbr;
	int				pipe_nbr;
	int				before_pipe;
	int				after_pipe;
	int				input;
	int				output;
	int				append;
	int				heredoc;
	char			**evnp;
	struct s_cmd	*next;
}	t_cmd;

// Parse
t_env	*create_env_node(char *env_str);
t_env	*init_new_list(char **envp);
char	*get_env_val(const char *name, t_env *env);
char	*replace_var_with_value(const char *input,
			const char *pos, char *value, size_t var_len);
char	*expand_env_variables(const char *input, t_env *env);
char	*append_var_to_result(char *result, const char *pos, size_t len);
size_t	extract_var_name(const char *pos, char *var_name);
void	check_quotes(char c, int *in_single_quote, int *in_double_quote);
char	*process_variable(char *result, char *pos,
			t_env *env, int in_single_quote);
char	*create_new_str(const char *input, size_t var_len, const char *pos);
char	*update_position(char *result, char *new_result, char *pos);
char	*compress_spaces(char *input);
char	*expand_and_compress(char *input, t_env *env);
int		check_pipe_error(const char *input, size_t i);
int		check_redirect_error(const char *input, size_t i);
t_cmd	*init_cmd(char	**evnp);
char	**ft_renew_evnp(char **evnp);
char	**ft_add_list(char **store);
int		handle_quote(char *cmd, int i, char quote_char);
char	*extract_command(char *cmd_line, int *i);
int		ft_get_parts(char *cmd);
char	*process_quotes_in_word(char *cmd, int *i);
void	skip_quotes(char *cmd, int *i);
void	fill_result(char *cmd, int start, int end, char *result);
int		is_empty_or_space_only(const char *input);
int		has_invalid_pipe_or_redirects(const char *cmd_line);
int		has_invalid_pipes(const char *cmd_line);
int		has_invalid_pipe_syntax(const char *cmd_line);

// new parse
t_cmd	*ft_start_parse(char *cmd_line, char **evnp);
char	**ft_deal_cmd(char *cmd);
void	ft_give_marks(t_cmd *cmd);
void	ft_handle_cmd_mark(t_cmd *cmd);
char	*ft_be_nice(char *input);
char	*extract_command(char *cmd_line, int *i);
int		ft_find_end(char *cmd_line, int i);
char	*create_command_substring(const char *cmd_line, int j, int i);
int		ft_check_quote(char *cmd);
int		ft_need_space(char *input);
// help functions
void	ft_print_cmd(t_cmd *cmd);
void	ft_print_doulbe_pointer(char **str);

// Execution
void	ft_execute(char **cmd, char **envp);
char	*ft_get_evn(char **envp, char *keyword, char *cmd);
void	ft_input(char *file_name);
void	ft_output(char *file_name);
void	ft_append(char *file_name);
void	ft_heredocs(char *end);
void	ft_export(char	**argv, char **evnp);
void	ft_cd(char *dest_dir);
void	ft_unset(char *str);
void	ft_record(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_start(t_cmd *cmd);
void	ft_read_and_print(void);
void	ft_wait_pid(pid_t *pid_first);
void	ft_check_and_execute(char **cmd, char **envp);
void	ft_exit(t_cmd *cmd);
void	ft_free_nods(t_cmd *cmd);
void	ft_free_double_pointer_char(char **output);
char	*ft_deal_record(int mark, char *str);
int		ft_renew_list(char *final);
int		ft_compare_strs(char *temp, char *final);
void	ft_unset(char *str);
char	*ft_delete_quote_before_equal(char *str);
char	**ft_add_list(char **store);
void	ft_print_env(char **evnp);
void	ft_print_double_pointer(char **str);
void	handle_pipes(t_cmd *temp, int **pipes, int *i_for_pipe);
int		handle_append(t_cmd *temp, t_cmd *search, t_cmd *start);
int		handle_output(t_cmd *temp, t_cmd *search, t_cmd *start);
void	handle_input(t_cmd *temp, t_cmd *search, t_cmd *start);
void	handle_heredoc(t_cmd *temp, t_cmd *search, t_cmd *start);
void	ft_run_cmd(t_cmd *cmd, int **pipes, pid_t *pids);
void	ft_free_double_pointer_int(int **pointer);
void	handle_parent_pipes(t_cmd *temp, int **pipes, int *i_for_pipe);

// Utils
size_t	ft_strlenn(const char *str);
char	*allocate_new_input(size_t len);
void	sigint_handler(int sig);
int		handle_dollar_sign(char **result,
			char **pos, t_env *env, int quotes[2]);
int		ft_isspace(int c);

#endif