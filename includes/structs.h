/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:20:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/05 14:46:58 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

extern int g_exit_status;

typedef struct t_env
{
    char *line;
    char *env_key;
    char *env_value;
    int is_printed;
    struct t_env *next;
} t_env;

typedef struct s_redir
{
    int type;
    char *name;
    int fd_in;
    int  fd_out;
    struct s_redir *next;
}t_redir;

typedef struct s_command
{
    char **arg;
    t_redir *redir;
    struct s_command *next_com;
} t_command;

typedef struct s_pipes
{
    int fd[2];
    int nb_cmd;
    pid_t pid;
    
} t_pipes;

#endif