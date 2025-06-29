/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:45 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 05:05:08 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
// # define SUCCESS_PTR ((void *)1)
// # define FAILURE_PTR ((void *)0)
# define PINK "\001\033[1;95m\002"
# define RESET "\001\033[0m\002"
# define BUFFER_SIZE 1024

void						print_listt(t_garbage *token);
int							check(char *line);
int							is_word(t_token_type type);
char						*create_string(char c);
int							is_red(t_token_type type);
int							is_special(char c);
char						*get_exp(char *var, t_env **env);

typedef struct s_garbage	t_garbage;

t_command					*parser(t_lexer *lexer);
// void print_listt(t_garbage *token);
int							check(char *line);
// void						*syntax_error(void);
int							parser_check(t_token *token);
t_command					*lexer(char *line);
t_command					*creat_comand_list(t_token *token, t_lexer *lexer);
// int *lexer(char *line);
// int syntax_error();
char						*get_env_value(t_env *env_list, const char *key);
t_env						*split_env(t_env *lst);
t_env						*init_env(char **envp);
void						*minishell(char *line, t_env **env);
char						*is_exp(char **token_val, t_env **env);
void						split_value(char *val, t_lexer *lexer,
								t_token *token);

/********************************************************* */
int							is_word(t_token_type type);
int							is_red(t_token_type type);
t_command					*new_comd(t_command **list, t_token *token);
void						fill_arg(t_command *comd, int f, t_token *token);
void						*handle_redirection(t_command *cur_comd,
								t_token **token, t_lexer *lexer);
int							is_space(char c);

/*from structs header*/
t_token						*handel_d_quotes(t_lexer *lexer);
t_token						*handel_s_quotes(t_lexer *lexer);
void						*herdoc_check(t_herdoc **herdoc, t_env **env);
char						*herdoc_expand(char *line, t_herdoc *herdoc);
int							handel_herdoc(t_env **env, t_token *token,
								t_redir *redir);
t_token						*handel_pipe(t_lexer *lexer);
t_token						*handel_dilim(t_lexer *lexer);
t_token						*handel_else(t_lexer *lexer);
t_token						*handel_word(t_lexer *lexer);
t_token						*handel_redir(t_lexer *lexer);
t_token						*handel_dollar(t_lexer *lexer);
int							has_dollar(char **s);
t_lexer						*init_lexer(char *line, t_env **env);
t_token						*set_token(t_token *token, char *cmd, int type);
t_token						*get_next_token(t_lexer *lexer);
void						append_token(t_token *old_token, char *s,
								t_lexer *lexer, int separ_red);
void						lexer_skip_white(t_lexer *lexer);
void						*adding_token(t_lexer *lexer, t_token *token);
int							reel_list(t_lexer *lexer, t_env **env);
void						*creat_new_token_exp(t_lexer *lexer, t_token *token,
								t_env **env);

/******************************************************** */

/******************************************************* */

/*from garbage colletctor header*/

// t_garbage **gc;

t_garbage					**getter(void);
char						*gc_strdup(const char *s1);
void						free_all(t_garbage **list);
void						*gc_malloc(size_t size, t_garbage **list);
// static t_garbage *get_last_node(t_garbage *list);
// static void add_node(t_garbage **list, t_garbage *new);

/******************************************* */
typedef struct s_cmd
{
	char					cmd;
	char					arg;
	int						type;
	char					*value;
	int						outfile;
	int						infile;
	void					*next;
}							t_cmd;

/****************************builins****************************/
void						print_listt(t_garbage *token);
int							check(char *line);
int							is_word(t_token_type type);
char						*create_string(char c);
char						*get_exp(char *var, t_env **env);
typedef struct s_garbage	t_garbage;
t_command					*parser(t_lexer *lexer);
// void print_listt(t_garbage *token);
int							check(char *line);
void						*syntax_error(char *s);
t_command					*lexer(char *line);
// int *lexer(char *line);
// int syntax_error();
char						*get_env_value(t_env *env_list, const char *key);
t_env						*split_env(t_env *lst);
t_env						*init_env(char **envp);
void						*minishell(char *line, t_env **env);
/********************************************************* */

t_garbage					**getter(void);
char						*gc_strdup(const char *s1);
void						free_all(t_garbage **list);
void						*gc_malloc(size_t size, t_garbage **list);
// static t_garbage *get_last_node(t_garbage *list);
// static void add_node(t_garbage **list, t_garbage *new);

/******************************************* */

typedef struct s_pipes		t_pipes;

/*----builtin----*/

void						ft_echo(t_command *cmd);
// void ft_pwd();
void						ft_pwd(t_command *cmd);
t_env						*init_env(char **envp);
int							is_buitins(t_command *list);
void						execute_buitlins(t_env **m_env, t_command *cmd);
// void print_env(char **envp, char **args);
t_env						*split_env(t_env *lst);
char						*get_env_value(t_env *env_list, const char *key);
char						*get_env_key(t_env *env_lst, const char *value);
void						set_env_value(t_env **env_list, char *key,
								char *value);
int							ft_cd(t_command *cmd, t_env **env);
void						ft_exit(t_command *args);
void						print_env(char **envp, char **args, int argc);
void						ft_export(t_env **env, t_command **args);
void						split_and_set(char *arg, t_env **splited_env_list);
void						ft_display_env(t_env *env, t_command *cmd);
// int ft_unset(t_command **cmd, t_env **env);
void						ft_unset(t_command **args, t_env **env);
int							is_valid_identifier(char *str);
void						handle_export_args(t_env **env, t_command *cmd);
// signals
void						signal_handler(int signal_num);
// execution
int							open_file(t_command *cmd);
void						execute_externals(t_command *cmd, t_env *env);
char						**get_envp(t_env *lst);
// multiple_pipes
pid_t						global_pipes(t_command *cmd, t_env **envp,
								int curr_cmd, t_pipes *p);
char						*search_cmd(t_command *cmd, t_env *lst);
void						*multiple_pipes(t_env **env, t_command *list);
int							first_command(t_command *cmd, t_env **envp,
								t_pipes p);
int							last_command(t_command *cmd, t_env **envp,
								t_pipes p);
int							mid_command(t_command *cmd, t_env **envp,
								t_pipes p);
int							ft_new_value(t_env *tmp, char *key, char *value,
								char *new_value);
void						update_line(t_env *node);
void						print_test(t_env *head);
void						free_key_value(char *key, char *value);
void						print_export(t_env *export);
void						dup2_close(t_redir *r);
void						handle_cases(t_command *cmd, t_env *env);
int							is_red(t_token_type type);
int							wait_children(t_pipes *p);
void						ft_clean(t_env **env);
void						helper_pipes(t_command *cmd, t_env **envp,
								t_pipes p);
void						helper_pipes1(t_command *cmd, t_env **envp);
int							check_file_status(t_command *file, t_env **env);
// int	handel_herdoc(t_env **env, t_token *token, t_redir *redir);
/*********signals*******/
void						signal_handler(int signal_num);
void						setup_signals_parent(void);
void						setup_signals_child(void);
void						ignore_signals(void);
void						setup_signals_heredoc(void);
void						sig_handler_heredoc(int signal);
#endif