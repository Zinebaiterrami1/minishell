#ifndef MIMI_H
#define MIMI_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef enum s_token_type
{
    T_COMMD,
    T_ARG,
    T_COTS,
    T_D_COTS,
    T_S_COTS,
    T_PAR,
    T_PIPE,
    T_RED_IN,
    T_RED_OUT,
    T_RED_IN_APEND,
    T_RED_OUT_APEND,
    T_APPEND,
    T_HERDOC,
    //T_EOF,

}t_token_type;

typedef struct s_token
{
    char *value;
    int type;
    struct s_token *next;
}t_token;

typedef struct s_check
{
    int parth_g;
    int parth_d;
    int s_quotes;
    int d_quotes;
    int quote_open;
}t_check;

typedef struct s_cmd
{
    char *comd;
    char *arg;
    int type;
    int outfile;
    int infile;

}t_cmd;

void free_tokens(t_token *tokens);
void skip_space(char *line, int *i);
char *handel_redir(char *line, int (*i), t_token *tokens);
void handel_pipe(t_token *tokens);
int select_d_cots(char *line, int i, t_token *tokens);
int check_d(char *line, int i);
char *handel_d_cots(char *line,int *i, t_token *tokens);
int select_s_cots(char *line, int i, t_token *tokens);
int check_s(char *line, int i);
char *handel_s_cots(char *line,int *i, t_token *tokens);
t_token *lexer(char *line);
void handel_pipe(t_token *tokens);
void handel_else(char *line, int *i, t_token *tokens);

#endif