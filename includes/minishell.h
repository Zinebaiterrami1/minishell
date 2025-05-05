#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include "mini.h"
#define BUFFER_SIZE 1024

typedef struct s_cmd
{
    char cmd;
    char arg;
    int type;
    char **copy_env;
    char *value;
    int outfile;
    int infile;
    void *next;
} t_cmd;

typedef struct t_env
{
    char *line;
    char *env_key;
    char *env_value;
    struct t_env *next;
} t_env;

extern int g_last_status;
/*----builtin----*/

void ft_echo(t_cmd *cmd);
void ft_pwd();
t_env *init_env(char **envp);
// void print_env(char **envp, char **args);
t_env *split_env(t_env *lst);
char *get_env_value(t_env *env_list, const char *key);
char *get_env_key(t_env *env_lst, const char *value);
void set_env_value(t_env **env_list, const char *key, const char *value);
int    ft_cd(char **args, t_env **env);
int	ft_exit(char **args);
void print_env(char **envp, char **args, int argc);

#endif