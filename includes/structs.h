/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:20:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/15 16:32:02 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "minishell.h"

extern int g_exit_status;

typedef struct t_env
{
    char *line;
    char *env_key;
    char *env_value;
    int is_printed;
    struct t_env *next;
} t_env;

typedef struct s_herdoc
{
    char *file_name;
    char *delimit;
    int fd;
    t_env **env;
}t_herdoc;

typedef struct s_redir
{
    int type;
    char *name;
    int fd_in;//why 2 fd
    int  fd_out;
    t_herdoc *herdoc;
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