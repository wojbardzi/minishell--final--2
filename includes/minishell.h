/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:25 by pzurawic          #+#    #+#             */
/*   Updated: 2025/08/12 22:18:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# define BUFFER_SIZE 100000000
# define QUOT_ERROR "Incorrect number of quotation marks\n"
# define CMD_ERROR "Instruction cannot ends with OPERATOR\n"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <ncurses.h>
# include <stdbool.h>
# include "./libft/libft.h"

typedef enum e_tokens
{
	ARG,
	BUILTIN,
	OPERATOR,
	QUOT,
}				t_tokens;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}				t_redir_type;

typedef struct s_data			t_data;
typedef struct s_parse			t_parse;
typedef struct s_token			t_token;
typedef struct s_exec			t_exec;
typedef struct s_redirection	t_redirection;

typedef struct s_data
{
	char			**envp;
	t_parse			*parsing;
	t_exec			*exec;
	pid_t			*pids;
}				t_data;

typedef struct s_token
{
	int				id;
	int				curr_ev;
	int				env_var_count;
	char			*text;
	char			**env_var;
	char			**envp;
	char			*proc_text;
	t_tokens		type;
}				t_token;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*filename;
	int						fd;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_exec
{
	char			*operator;
	char			*cmd;
	char			**args;
	char			**envp;
	int				out;
	int				in;
	t_redirection	*redirections;
	t_tokens		token;
	struct s_exec	*next;
	struct s_exec	*prev;
}				t_exec;

typedef struct s_parse
{
	char		*input;
	char		**words;
	char		*operators;
	int			input_items;
	t_token		**tokens;
	t_data		*data;
}				t_parse;

void			clear_pids(t_data *data);
void			sigaction_error(int signal);
void			interactive_mode_signals(t_data *data);
void			handle_operator(t_exec **exec, t_parse *parsing, int *i);
void			handle_command(t_exec **exec, t_parse *parsing, int *i);
int				execute_command(t_data *data, t_exec *command_struct);
int				execute_pipeline(t_data *data);
int				is_builtin_command(char *cmd);
char			*find_path(const char *cmd);
int				handle_heredoc(const char *delimiter);
int				handle_execve_path(t_data *data, t_exec *command_struct);
void			handle_execve_direct(t_exec *command_struct);
bool			input_reader(t_data *data);
void			error_exit(void);
void			exit_clear(t_data *data);
void			free_tokens(t_parse *parsing);
void			free_double_array(char **array);
void			free_exec_redirections(t_redirection *redirections);
void			free_tokens_recursive(t_token **tokens, int count);
void			clear_data(t_data *data);
void			clear_parsing_data(t_parse *parsing);
void			clear_exec_data(t_exec *exec);
void			set_parsing(t_parse *parsing, t_data *data);
int				is_redirection_operator(char *str);
int				is_redirection_operator2(const char *str);
void			add_arg_to_cmd(t_exec *exec, char *arg);
int				is_redirect_operator(const char *str);
int				set_operator_priority(char *operator);
bool			debug_exec_struct(t_exec *exec);
bool			debug_exec_struct_detailed(t_exec *exec);
void			debug_tokens(t_token **tokens, int count);
void			debug_words(char **words, int count);
int				ft_isspace(char c);
int				count_double_array(char **array);
int				is_valid_identifier(const char *str);
void			push_to_exec(t_parse *parsing, t_exec *exec);
void			push_cmd_to_exec(t_exec **exec, t_token *token);
void			push_operator_to_exec(t_exec **exec, t_token *token);
void			push_redir_in_to_exec(t_exec **exec, t_token *token,
					t_token *file);
void			push_redir_out_to_exec(t_exec **exec, t_token *token,
					t_token *file);
void			push_redir_append_to_exec(t_exec **exec, t_token *token,
					t_token *file);
void			push_redir_heredoc_to_exec(t_exec **exec, t_token *token,
					t_token *file);
int				add_redirection(t_exec *exec, t_redir_type type,
					char *filename);
t_exec			*create_new_exec_node(void);
int				handle_env_variable(char *word, char **envp, char **result);
void			push_to_exec_help(t_exec **exec, t_token *token);
bool			parsing_main(t_data *data);
void			process_text(t_token *token);
void			handle_envp_in_word(t_token *token);
void			parse_tokens(t_data *data);
void			parsing_tokens_words(t_data *data);
char			*process_text_copy(char *input, char **envp);
int				expand_env_var(char *input, int *i, char **result,
					char **envp);
void			copy_regular_char(char *input, int *i, char **result);
int				find_var_end(char *input, int start);
char			*get_env_value(char *var_name, char **envp);
void			expand_exit_code(char **result);
void			concatenate_result(char **result, char *addition);
void			init_result(char **result);
int				handle_special_variables(char *input, int *i, char **result,
					char **envp);
int				handle_regular_variable(char *input, int *i, char **result,
					char **envp);
void			process_text_copy_utils(char *input, int *i, char **result);
void			process_text_utils(t_token *token, char **envp);
bool			check_if_builtin(char *cmd);
void			validate_tokens(t_data *data);
int				validate_quotes(char *input);
int				validate_operators(t_data *data);
bool			check_unclosed_quotes(char *input);
bool			check_invalid_operators(t_data *data);
void			tokenize(t_parse *parsing);
void			set_words_tab(t_parse *parsing);
int				parsing(t_data *data);
void			set_data(t_data *data, char **envp);
char			**unset_env_var(char **envp, char *var_name);
int				is_valid_unset_name(char *name);
char			**remove_env_var(char **envp, int index);
int				find_env_var_index(char **envp, char *var_name);
char			*extract_var_name(char *env_entry);
void			free_and_copy_envp(char **old_envp, char **new_envp);
int				export_var(char *arg, t_data *data);
void			print_export_vars(char **envp);
char			**sort_envp_for_export(char **envp);
int				is_valid_export_syntax(char *arg);
char			*extract_export_name(char *arg);
char			*extract_export_value(char *arg);
int				update_existing_var(char **envp, char *name, char *value);
char			**add_new_var(char **envp, char *name, char *value);
int				count_envp_vars(char **envp);
char			*create_env_entry(char *name, char *value);
void			bubble_sort_envp(char **envp, int count);
int				compare_env_names(char *env1, char *env2);
char			*get_env_name(char *env_entry);
void			print_sorted_export(char **sorted_envp);
void			format_export_output(char *env_entry);
int				cd_to_directory(char *path, t_data *data);
int				cd_to_home(t_data *data);
int				cd_to_oldpwd(t_data *data);
char			*get_env_var_value(char **envp, char *name);
int				update_pwd_vars(char *old_pwd, char *new_pwd, t_data *data);
int				set_env_var(char **envp, char *name, char *value,
					t_data *data);
char			*resolve_cd_path(char *path);
int				change_directory(char *path);
int				validate_cd_path(char *path);
char			*get_current_directory(void);
int				handle_cd_error(char *path);
int				is_directory(char *path);
void			redirect_builtin_output(t_exec *exec_node);
void			restore_builtin_output(int saved_stdout);
void			set_exec_envp(t_exec *exec, char **envp);
int				is_correct(t_exec *exec);
char			*get_current_path(void);
char			*determine_target_path(t_exec *exec, t_data *data);
int				change_dir(char *temp_path);
void			cd_change_envp(char *new_pwd, char *old_pwd, t_data *data);
void			execute_builtin(t_data *data, t_exec *exec);
int				builtin_echo(t_exec *exec);
void			builtin_exit(t_exec *exec, t_data *data);
int				validate_exit_args(t_exec *exec, t_data *data);
int				builtin_export(t_exec *exec, t_data *data);
int				builtin_unset(t_exec *exec, t_data *data);
int				builtin_cd(t_exec *exec, t_data *data);
int				builtin_pwd(void);
int				builtin_env(char **args, char **envp);
int				count_args_in_envp(char **envp, char **args);
char			**allocate_new_envp(char **envp, int vars_to_remove);
char			**build_new_envp(char **envp, char **new_envp, char **args);
void			free_data_envp(t_data *data);
void			print_sorted_array(char **envp);
bool			is_valid(char *arg);
void			update_envp(t_data *data, t_exec *exec, int *j);
void			bubble_sort(char **arr, int size);
char			**create_new_envp(char **envp);
char			*prepare_envp_entry(char *arg);
void			create_and_update_envp(t_data *data, char *arg);
bool			look_for_operator(char c);
void			clear_parsing(t_parse *parsing);
void			clear_exec(t_exec *exec);
int				is_separator(t_parse *parsing, int i);
void			set_operators(char *operators);
void			free_words(t_parse *parsing);
void			cleanup_redirections(t_redirection *redirections);
int				skip_squot(char *text);
int				dec_by_quot_mark(t_token *token, int len);
void			envp_handler(t_token *token);
void			copy_text(t_token *token, int len, char quot_mark);
int				parse_command_with_redirections(t_parse *parsing, t_exec *exec,
					int *index);
t_exec			*alloc_exec(void);
void			alloc_proc_text(t_token *token, int len);
void			track_quot_mark(t_token *token, char *quot_mark, int i);
int				env_var_count(t_token *token);
void			get_env_var(t_token *token, int *i, int *j, char *value);
void			alloc_env_var(t_token *token);
int				setup_pipe(t_exec *curr, int *pipe_fd);
void			save_stdio(int *saved_stdin, int *saved_stdout);
void			restore_stdio(int saved_stdin, int saved_stdout);
int				redirect_io(int in, int out);
void			close_fds(int prev_fd, int out_fd);
int				pipeline_loop(t_data *data, int *status);
int				apply_redirections(t_exec *exec);
int				open_redirection_file(t_redirection *redir);
int				fill_args_array(t_parse *parsing, char **args,
					int start, int end);
int				setup_exec_cmd(t_exec *exec, char **args, int arg_count);
int				count_args(t_parse *parsing, int start, int end);
int				handle_redirection_token(t_parse *parsing, t_exec *exec,
					int *i, int end);
int				init_pipeline_vars(t_data *data, pid_t **pids, int *max_pids);
int				is_single_builtin_check(t_exec *current);
void			kill_all_processes(pid_t *pids, int pid_count);
int				setup_signal_mask(sigset_t *mask, t_data *data);
void			setup_sigint(t_data *data);
void			setup_sigquit(t_data *data);
void			setup_sigpipe(t_data *data);

extern int	g_exit_code;

#endif
