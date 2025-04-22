#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include "mini.h"
#define BUFFER_SIZE 1024

typedef struct s_cmd
{
    char comd;
    char arg;
    int type;
    int outfile;
    int infile;

}t_cmd;

/*----builtin----*/

void ft_echo(t_token *cmd);
void ft_pwd();
#endif