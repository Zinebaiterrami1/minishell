#ifndef MIMI_H
#define MIMI_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "garbage_collector/gc.h"

typedef enum s_token_type
{//1
    T_ARG,//2//3
    T_D_COTS,//4
    T_S_COTS,//5
    T_PAR,//6
    T_PIPE,//7
    T_RED_IN,//8
    T_RED_OUT,//9
    T_RED_IN_APEND, //10
    T_RED_OUT_APEND,
    T_APPEND,//12
    T_HERDOC,
    T_WORD,//14
    T_DOLLR,
    T_EXP,//16
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

typedef struct s_file
{
    int fd;
    t_token_type type;
    char *name;
    char *limiter;
    int expand;

}t_file;


typedef struct s_cmd
{
    char *comd;
    char *arg;
    int type;
    t_file *outfile;
    t_file *infile;

}t_cmd;

// void free_tokens(t_token *tokens);
// void skip_space(char *line, int *i);
// char *handel_redir(char *line, int (*i), t_token *tokens);
// void handel_pipe(t_token *tokens);
// int select_d_cots(char *line, int i, t_token *tokens);
// int check_d(char *line, int i);
// char *handel_d_cots(char *line,int *i, t_token *tokens);
// int select_s_cots(char *line, int i, t_token *tokens);
// int check_s(char *line, int i);
// char *handel_s_cots(char *line,int *i, t_token *tokens);
// t_token *lexer(char *line);
// void handel_pipe(t_token *tokens);
// void handel_else(char *line, int *i, t_token *tokens);

#endif