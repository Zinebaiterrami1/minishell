/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:20:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/28 21:02:56 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct t_env
{
    char *line;
    char *env_key;
    char *env_value;
    struct t_env *next;
} t_env;

typedef struct s_redir
{
    int type;
    char *name;
    struct s_redir *next;
}t_redir;

typedef struct s_command
{
    char **arg;
    int fd_in;
    int fd_out;
    char *path;
    t_redir *redir;
    struct s_command *next_com;
} t_command;


#endif