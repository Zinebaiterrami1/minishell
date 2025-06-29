/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:20:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/29 05:05:23 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"
# include <unistd.h>

extern int				g_exit_status;

typedef struct t_env
{
	char				*line;
	char				*env_key;
	char				*env_value;
	int					is_printed;
	struct t_env		*next;
}						t_env;

typedef struct s_herdoc
{
	char				*file_name;
	char				*delimit;
	int					fd;
	t_env				**env;
}						t_herdoc;

typedef struct s_redir
{
	int					type;
	char				*name;
	int					fd_in;
	int					fd_out;
	t_herdoc			*herdoc;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**arg;
	t_redir				*redir;
	struct s_command	*next_com;
}						t_command;

typedef struct s_pipes
{
	int					fd[2];
	int					nb_cmd;
	pid_t				pid;
}						t_pipes;

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
}						t_token_type;

typedef struct s_garbage
{
	void				*adress;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_token
{
	char				*value;
	int					type;
	int					space;
	int					d_quotes;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer
{
	char				c;
	char				*line;
	int					status_d;
	int					status_s;
	int					error;
	unsigned int		i;
	t_token				*head;
	t_token				*reel_head;
	t_env				**env;
	size_t				line_size;
}						t_lexer;

typedef struct s_check
{
	int					parth_g;
	int					parth_d;
	int					s_quotes;
	int					d_quotes;
	int					quote_open;
}						t_check;

typedef struct s_file
{
	int					fd;
	t_token_type		type;
	char				*name;
	char				*limiter;
	int					expand;
}						t_file;

#endif