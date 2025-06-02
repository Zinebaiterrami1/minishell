/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:45 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/02 14:00:57 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "structs.h"
#include "../parsing/mimi.h"
#include "../libft/libft.h"
#define BUFFER_SIZE 1024

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



extern int g_last_status;
/*----builtin----*/

void ft_echo(t_command *cmd);
void ft_pwd();
t_env *init_env(char **envp);
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
void ft_display_env(t_env *env);
// int ft_unset(t_command **cmd, t_env **env);
void ft_unset(t_command **args, t_env **env);
int is_valid_identifier(const char *str);
//signals
void signal_handler(int signal_num);
//execution 
int open_file(t_command *cmd);
void execute_externals(t_command *cmd, t_env *env);
char** get_envp(t_env *lst);
#endif