#ifndef MIMI_H
#define MIMI_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "garbage_collector/gc.h"

#define SUCCESS_PTR ((void *)1)
#define FAILURE_PTR ((void *)0)

#define PINK "\001\033[1;95m\002"
#define RESET "\001\033[0m\002"

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
    //T_EOF,

}t_token_type;

typedef struct s_token
{
    char *value;
    int type;
    int space;
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

typedef struct s_redir
{
    int type;
    char *name;
    struct s_redir *next;
}t_redir;

typedef struct s_command
{
    char **arg;
    t_redir *redir;
    struct s_command *next_com;
} t_command;


t_command *parser(t_lexer *lexer);
void print_listt(t_garbage *token);
int check(char *line);
void *syntax_error();
char *get_env_value(t_env *env_list, const char *key);
t_env *split_env(t_env *lst);
t_env *init_env(char **envp);
int is_word(t_token_type type);
char *create_string(char c);
char *get_exp(char *var, char **env);
int is_red(t_token_type type);



#endif