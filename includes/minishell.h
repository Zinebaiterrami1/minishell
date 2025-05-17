/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:45 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/16 20:16:56 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include "../libft/libft.h"
#include "../parsing/mimi.h"
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

typedef struct t_env
{
    char *line;
    char *env_key;
    char *env_value;
    struct t_env *next;
} t_env;

extern int g_last_status;
/*----builtin----*/

void ft_echo(t_command *cmd);
void ft_pwd();
t_env *init_env(char **envp);
// void print_env(char **envp, char **args);
t_env *split_env(t_env *lst);
char *get_env_value(t_env *env_list, const char *key);
char *get_env_key(t_env *env_lst, const char *value);
void set_env_value(t_env **env_list, const char *key, const char *value);
int ft_cd(t_command *cmd, t_env **env);
int	ft_exit(char **args);
void print_env(char **envp, char **args, int argc);
int ft_export(char **args, t_env **env);
void ft_display_env(t_env *env, char **envp);
#endif