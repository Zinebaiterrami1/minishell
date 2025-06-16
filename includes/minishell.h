/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:45 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/16 16:19:08 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h> 
#include "structs.h"
#include "../libft/libft.h"
// #include "../parsing/garbage_collector/gc.h"


#define SUCCESS_PTR ((void *)1)
#define FAILURE_PTR ((void *)0)

#define PINK "\001\033[1;95m\002"
#define RESET "\001\033[0m\002"

#define BUFFER_SIZE 1024

extern int g_exit_status;




/*from mimi header*/
typedef enum s_token_type
{
    T_D_COTS,
    T_S_COTS,
    T_PIPE,
    T_RED_IN,
    T_RED_OUT,
    T_RED_OUT_APEND,
    T_HERDOC,
    T_WORD,
    T_EXP,
    
}t_token_type;

typedef struct s_garbage
{
    void *adress;
    struct s_garbage *next;
}t_garbage;

typedef struct s_token
{
    char *value;
    int type;
    int space;//i have a probleme that whene the words are not separated by space my tokenizer separate them and this shouldnt hapen 
    int d_quotes;
    struct s_token *next;
}t_token;


typedef struct s_lexer
{
    char c;
    char *line;
    int status_d;
    int status_s;
    int error;
    unsigned int i;
    t_token *head;
    t_token *reel_head;
    t_env **env;
    size_t line_size;
}t_lexer;

typedef struct s_check
{
    int parth_g;
    int parth_d;
    int s_quotes;
    int d_quotes;
    int quote_open;
}t_check;

typedef struct s_file
{
    int fd;
    t_token_type type;
    char *name;
    char *limiter;
    int expand;
}t_file;

// typedef struct t_env
// {
//     char *line;
//     char *env_key;
//     char *env_value;
//     struct t_env *next;
// } t_env;

// typedef struct s_redir
// {
//     int type;
//     char *name;
//     struct s_redir *next;
// }t_redir;

// typedef struct s_command
// {
//     char **arg;
//     t_redir *redir;
//     struct s_command *next_com;
// } t_command;


void print_listt(t_garbage *token);
int check(char *line);


int is_word(t_token_type type);
char *create_string(char c);
char *get_exp(char *var, t_env **env);

typedef struct s_garbage t_garbage;


t_command *parser(t_lexer *lexer);
// void print_listt(t_garbage *token);
int check(char *line);
void *syntax_error();
t_command *lexer(char *line);
// int *lexer(char *line);
// int syntax_error();
char *get_env_value(t_env *env_list, const char *key);
t_env *split_env(t_env *lst);
t_env *init_env(char **envp);
void *minishell(char *line, t_env **env);
/********************************************************* */

/*from structs header*/

extern int g_exit_status;

// typedef struct t_env
// {
//     char *line;
//     char *env_key;
//     char *env_value;
//     int is_printed;
//     struct t_env *next;
// } t_env;

// typedef struct s_redir
// {
//     int type;
//     char *name;
//     int fd_in;
//     int  fd_out;
//     struct s_redir *next;
// }t_redir;

// typedef struct s_command
// {
//     char **arg;
//     t_redir *redir;
//     struct s_command *next_com;
// } t_command;

// typedef struct s_pipes
// {
//     int fd[2];
//     int nb_cmd;
//     pid_t pid;
    
// } t_pipes;
/******************************************************* */

/*from garbage colletctor header*/

// t_garbage **gc;


t_garbage **getter();
char	*gc_strdup(const char *s1);
void free_all(t_garbage **list);
void *gc_malloc(size_t size, t_garbage **list);
// static t_garbage *get_last_node(t_garbage *list);
// static void add_node(t_garbage **list, t_garbage *new);

/******************************************* */
typedef struct s_cmd
{
    char cmd;
    char arg;
    int type;
    char *value;
    int outfile;
    int infile;
    void *next;
} t_cmd;

typedef struct s_pipes t_pipes;

extern int g_last_status;
/*----builtin----*/

void ft_echo(t_command *cmd);
void ft_pwd();
t_env *init_env(char **envp);
int is_buitins(t_command *list);
void execute_buitlins(t_env **m_env, t_command *cmd);
// void print_env(char **envp, char **args);
t_env *split_env(t_env *lst);
char *get_env_value(t_env *env_list, const char *key);
char *get_env_key(t_env *env_lst, const char *value);
void set_env_value(t_env **env_list, char *key, char *value);
int ft_cd(t_command *cmd, t_env **env);
void ft_exit(t_command *args);
void print_env(char **envp, char **args, int argc);
void ft_export(t_env **env, t_command **args);
void split_and_set(char *arg, t_env **splited_env_list);
void ft_display_env(t_env *env, t_command *cmd);
// int ft_unset(t_command **cmd, t_env **env);
void ft_unset(t_command **args, t_env **env);
int is_valid_identifier(char *str);
void	handle_export_args(t_env **env, t_command *cmd);
//signals
void signal_handler(int signal_num);
//execution 
int open_file(t_command *cmd);
void execute_externals(t_command *cmd, t_env *env);
char** get_envp(t_env *lst);
//multiple_pipes
pid_t global_pipes(t_command *cmd, t_env **envp, int curr_cmd, t_pipes *p);
char* search_cmd(t_command *cmd, t_env *lst);
void *multiple_pipes(t_env **env, t_command *list);
int first_command(t_command *cmd, t_env **envp, t_pipes p);
int last_command(t_command *cmd, t_env **envp, t_pipes p);
int mid_command(t_command *cmd, t_env **envp, t_pipes p);

void	print_test(t_env *head);
#endif