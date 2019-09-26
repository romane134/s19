/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <bjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:06:13 by bjovanov          #+#    #+#             */
/*   Updated: 2019/09/18 17:45:50 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H
# define SHELL_NAME "42SH"
# define FC_OPTION_R 1
# define FC_OPTION_N 2
# define FC_OPTION_L 4
# define FC_OPTION_E 8
# define FC_OPTION_S 16
# define FC_OPTION_STOP 32
# define FC_OPTION_END 64
# define DEFAULT_TEXT_EDITOR "vim" //Remplace by ed after debug !
# include "../libft/includes/libft.h"
# include <term.h>
# include "termcaps.h"
//# include "job_control.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
#include <stdio.h>

enum	e_tokens {

	TILDE_TOKEN,
	DOLLAR_TOKEN,
	DOLLARBRACE_TOKEN,
	DGREAT_TOKEN,
	DLESS_TOKEN,
	OR_IF_TOKEN,
	LESSGREAT_TOKEN,
	LESSAND_TOKEN,
	GREATAND_TOKEN,
	ANDGREAT_TOKEN,
	AND_IF_TOKEN,
	PIPE_TOKEN,
	JOBCONTROL_TOKEN,
	GREAT_TOKEN,
	LESS_TOKEN,
	RBRACE_TOKEN,
	SEMICOLON_TOKEN,
	ASSIGN_TOKEN,
	HISTORY_TOKEN,
	SUBSHELL,
	BRACE_GROUP,
	COMMAND_TOKEN,
	DQUOTE,
	QUOTE,
};

typedef struct				s_pwd
{
	char					*pwd;
	char					*oldpwd;
}							t_pwd;

typedef struct				s_std
{
	int						out;
	int						err;
}							t_std;

typedef struct				s_redirect
{
	char					*path;
	enum e_tokens			name;
	int						std;
	struct s_redirect		*next;
}							t_redirect;

typedef struct				s_history
{
	char					*opening;
	char					*closing;
	struct s_history		*next;
}							t_history;

typedef struct				s_handled_token
{
	char					*value;
	enum e_tokens			name;
	int						priority;
	char					*closing;
	int						splitter;
	struct s_handled_token	*next;
}							t_handled_token;

typedef struct				s_token
{
	struct s_token			*next;
	struct s_token			*prev;
	struct s_token			*right;
	struct s_token			*left;
	struct s_token			*parent;
	char					*value;
	enum e_tokens			name;
	int						priority;
}							t_token;

typedef struct				s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct				s_hash
{
	char					*key;
	void					*data;
	int						nb;
	struct s_hash			*next;
}							t_hash;

typedef struct				s_internal
{
	char					*key;
	char					*value;
	struct s_internal		*next;
}							t_internal;

typedef struct				s_shell
{
	char					**env;
	t_internal				*in;
	t_handled_token			*handled_token;
	t_pwd					*pwd;
	int						sig;
	int						exit_status;
	t_termcaps				*termcaps;
	int						i;
	t_hash					**intern_hash;
	t_hash					**alias_hash;
	int						stop;
	int						stdin_copy;
}							t_shell;

extern t_shell				*g_shell;
extern t_hash				**g_hash_table;

# define HASHTABLE_SIZE		4096
# define INTERN_HASH_SIZE	4219
# define ALIAS_HASH_SIZE	4219

# define MALLOC_FAILURE		104
# define BAD_SUB_CODE		103

void 						sign_handler(int sig);
void						sign_child(int sig);
void						init_job(void);
void						create_new_cmd(char **cmd, int i, int *ban_index);
void						find_index_to_ban(char *cmd, int k,
	int **ban_index, t_history **history);
void						clear_cmd(char **cmd);
void						stop(int nb);
void						reset_stdin(void);
char						*reader(void);
void						sig(int nb);
void						exit_shell(char *error);
int							exit_shell_code(char *error, int error_code);
int							syntax_error(char *token);

char						*ft_getenv(char *name);
char						*ft_getenv_choice(char *name, char **env);
void						set_pwd(void);

void						bootstrap(char **env);
void						set_environment(char **env);

void						add_env_item_last(char *key, char *value);
void						add_env_item_first(char *key, char *value);

void						delete_array(char **array1);
void						free_array_exit(char *array);

void						set_handled_token(void);
void						add_handled_token(char *value, enum e_tokens name,
		int priority, int splitter);
void						add_front_token(t_token **tokens, char *value,
		enum e_tokens name, int priority);

void						set_hash(int construct);

void						print_handled_token_list(t_handled_token *tokens);
void						print_history(t_history *history);
void						print_token_list(t_token *tokens);

int							count_backslashes(char *line, int i);
t_token						*lexer(char **line);
int							check_token_list(t_token **tokens, char **line,
		t_termcaps	*term);
void						clear_token_list(t_token **tokens);
void						order_redirection(t_token **tokens);
int							is_redirect_token(enum e_tokens name);
void						delete_token_list(t_token **tokens);
size_t						handle_redirect(char *line, int *i, int *length,
		t_handled_token *current);
t_token						*redirection_not_ordered(t_token *tokens);
void						delete_token(t_token **tokens, t_token **begin);
t_handled_token				*is_closing_token(char *line, int i);
t_handled_token				*is_splitter_token(char *line, int i);
void						add_token(t_token **tokens, char *value,
		enum e_tokens name, int priority);
int							count_words_redirection(char *var, int *quote);
int							is_token(char *token);
int							token_lst_len(t_token *token);
int							is_only_space(char *line);

/*
 ** close command
*/

void						close_command(char **line, t_termcaps	*termcaps);
int							check_line(char **line, t_history *history,
							t_termcaps *t);

void						add_history(t_history **history, char *opening,
		char *closing);
void						remove_last_history(t_history **history);
const char					*get_last_history_opening(t_history *history);
const char					*get_last_history_closing(t_history *history);

int							exec(t_token *ast, char ***env);

/*
 ** PARSEUR HEADERS
*/

t_token						*parseur(t_token *list);
void						ast_left(t_token *li);
void						ast_right(t_token *li);
t_token						*ast_start(t_token *li);
void						*find_hash(t_hash **array, char *key, int i);
int							total_ascii(char *s);
int							find_index_key(char *s, int size);
t_hash						**make_hash(int size);
void						add_data_hash(char *key, void *data, int size,
							t_hash **array);
void						del_hash(char *key, int size, t_hash **array);
void						del_all_hash(t_hash **array, int size);
void						print_all_hash_str(t_hash **array, int size);

int							exec_pipe(t_token *ast, char ***env);
int							exec_command(t_token *ast, char ***env);
int							exec_core(t_token *ast, char **cmd, char ***env,
	int i);
int							exec_semicolon(t_token *ast, char ***env);
int							exec_redirect(t_token *ast, char ***env);
int							exec_left_redirect(t_token *ast, int position);
int							exec_andgreat(t_token *ast, char **env);
int							exec_orif(t_token *ast, char ***env);
int							exec_andif(t_token *ast, char ***env);

int							free_array(char *array, int return_value);
int							free_darray(char **array, int return_value);
int							free_array_int(int *array, int return_value);

void						add_redirect_item(t_redirect **redirect, char *path,
							enum e_tokens name, int std);

int							is_builtin(char *cmd);
int							try_builtin(t_token *ast, char **cmd, int i,
	char ***env);
int							expansions_handle(char **command, char **environ);
void						expansion_dollar(char **cmd, char **environ);
void						expansion_tilde(char **cmd, char **environ);
int							expansion_history(char **cmd);
void						print_error(char *component, char *error);
int							find_in_array(char **array, char *to_find);
int							is_escaped(char *command, int i);
char						*get_varname(char *command);
int							is_in_env(char *varname, char **environ);
int							set_underscore_var(char **cmd, char ***env);
int							is_only_alphanum(char *cmd);
int							is_an_intern(char *varname, char **cmd);
int							is_question_mark(char *varname, char **cmd);
int							has_bad_substitution(char *cmd);
char						**dup_env(char **environ);
void						set_temp_env(char **var, char ***tmp_env,
	char ***env);
int							check_validity(char *path_cmd, char *cmd);

int							is_escape_backslash(char *cmd, int i);
void						recognize_quote(int **quote, char *str);
int							look_for_close_brace(char *var, int i);
void						set_intern_var(char **var);
char						**parse_cmd(char *var);
void						clear_cmd(char **cmd);
int							is_bad_substitution(char **cmd, int j, int i);
int							print_error_return(char *component, char *error,
	int value_return);

int							delete_redirect(t_redirect **redirect, int status);
void						handle_left_redirect(t_token *list,
							t_termcaps *termcaps);

int							is_dash(char *fd);
int							is_valid_fd(char *fd);
int							is_right_redirect(enum e_tokens name);
int							check_fd(char *fd);
void						create_files(t_redirect *tmp, int *file);

void						dup_to_both(int *file, t_redirect *tmp);
void						dup_to_stdin(int *file, t_redirect *tmp);
void						dup_to_stdout(int *file, t_redirect *tmp);
void						dup_to_stderr(int *file, t_redirect *tmp);
void						dup_files(t_redirect *files, int *file);

int							print_env(char **env);
void						builtin_exit(char **cmd, t_token *ast);
int							builtin_setenv(char **cmd, char ***env);
int							builtin_unsetenv(char **cmd, char ***env);
int							builtin_echo(char **cmd);
int							builtin_env(char ***env, char **cmd);
int							delete_array_print(char **env);
int							builtin_cd(char ***env, char **cmd);
int							setenv_tmp_env(char *cmd, char ***env, int *end);
char						*find_path(char *cmd);
int							find_index(char **cmd, int i);
char						**strdup_array(char **env, int j);
int							is_valide_key(char *key);
int							is_variable_env(char *cmd, char c);
int							error_option(char option);
int							error_setenv_tmp(char *c);
int							print_error_path(char *cmd, int i, char *path);
int							usage_error(char c);
int							cd_error(char *cmd, int i);
void						call_set_env(char ***env);
int							construct_full_path(char *path, char ***env);
void						prev_path(char **cur);
char						*set_sym_path(int i, char **sym, char **splitted);
char						*get_sym_path(char *cur, char *path);
int							get_path(char *cmd, char **path, char ***env);
int							get_option(char **cmd, char *option);
char						**create_key_value_env(char *item, char *path);
int							cd_p_option(char *cmd, char ***env);
int							cd_no_option(char *cmd, char ***env);
void						exec_child_dless_token(int fd[2], char *value);

/*
** math.c
*/
int							val_abs(int nbr);
int							bigger(size_t a, size_t b);

/*
**builtin_hash
*/
void						hash_builtin(void);

int							get_history_len();

int							builtin_fc(char **cmd);
int							fc_option_l(char **cmd, int g_bit, int i, int fd);
int							get_first_last(char **cmd, int i, int *first,
	int *last);
int							check_fc_option(char **s1, int *g_bit);
char						*get_new_cmd(void);
char						*get_editor(char **cmd, int *i, int g_bit);
int							get_first_last(char **cmd, int i, int *first,
	int *last);
int							fc_error(int i, char *cmd);
void						start_process(char *line);

#endif
