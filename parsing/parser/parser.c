/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/19 12:53:07 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//"$$$HOME"

int	is_word(t_token_type type)
{
	if (type == T_WORD || type == T_D_COTS || type == T_EXP || type == T_S_COTS)
		return (1);
	return (0);
}

int	parser_check(t_token *token)
{
	if (token && token->type == T_PIPE)
		return (EXIT_FAILURE);
	while (token)
	{
		if (token->type == T_PIPE && (token->next == NULL
				|| token->next->type == T_PIPE || *(token->next->value) == '('
				|| *(token->next->value) == ')'))
			// exampel ehco hi > $a  | cat << hi ||
			return (EXIT_FAILURE);
		// if(token->type == T_RED_IN || token->type == T_RED_OUT
		// || token->type == T_RED_IN
			// || token->type == T_HERDOC)//should be checked wile herdoc is opning
		// {
		//     if (token->next == NULL || !is_word(token->next->type))
		//     return(EXIT_FAILURE);
		// }
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	is_red(t_token_type type)
{
	if (type == T_RED_OUT || type == T_RED_IN || type == T_RED_OUT_APEND
		|| type == T_HERDOC)
		return (1);
	return (0);
}
// t_token *fill_command(t_token *token, t_command *comd, int count)
// {
//     int i;

//     i = 0;
//     while(i < count)
//     {
//         if(token->type == T_WORD || token->type == T_D_COTS
//            || token->type == T_EXP || token->type == T_S_COTS)
//         {
//             comd->arg[i] = gc_strdup(token->value);
//             i++;
//         }
//         else if (token->type == T_RED_OUT || token->type == T_RED_IN
//             || token->type == T_RED_OUT_APEND || token->type == T_HERDOC)
//         {
//             comd->redir;
//         }
//         token = token->next;
//     }
//     return(token);
// }

// t_command *get_command(t_token **token, t_command *list)
// {
//     t_command *comd;
//     int count;
//     t_token *cur;
//     int i;

//     i = 0;
//     count = 0;
//     cur = (*token);
//     while(cur->type != T_PIPE)
//     {
//         count++;
//         cur = cur->next;
//     }
//     comd =
//     comd->arg = gc_malloc(sizeof(char *) * (count + 1), getter());
//     (*token) = fill_command(*token, comd, count);

// }

void	add_command(t_command **list, t_command *new)
{
	t_command	*ptr;

	if (new == NULL || !list)
		return ;
	ptr = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (ptr->next_com)
	{
		ptr = ptr->next_com;
	}
	if (ptr)
		ptr->next_com = new;
	return ;
}

t_command	*new_comd(t_command **list, t_token *token)
{
	t_command	*comd;
	t_token		*cur;
	int			count;

	count = 0;
	cur = token;
	comd = gc_malloc(sizeof(t_command), getter());
	while (cur)
	{
		if (is_red(cur->type) && cur->next)
			cur = cur->next->next;
		else
		{
			count++;
			cur = cur->next;
		}
	}
	printf("count = %d\n", count);
	comd->arg = gc_malloc(sizeof(char *) * (count + 1), getter());
	comd->next_com = NULL;
	comd->redir = NULL;
	add_command(list, comd);
	if (comd)
		return (comd);
	return (NULL);
}

void	fill_arg(t_command *comd, int f, t_token *token)
{
	comd->arg[f] = gc_strdup(token->value);
	printf("argg = ___%s\n", token->value);
}

void	add_redir(t_redir **list, t_redir *new)
{
	t_redir	*ptr;

	if (new == NULL || !list)
		return ;
	ptr = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	if (ptr)
		ptr->next = new;
	return ;
}

// while(!acsec(name, f_ok))
//     name = strjoin(name. atoi(1));

int	has_quotes(t_token *token)
{
	if (token->type == T_D_COTS || token->type == T_S_COTS)
		return (1);
	return (0);
}

void	skip_dollar(char *line, int *i)
{
	while (line[*i] == '$' && line[*i + 1] && line[*i + 1] == '$')
		(*i) += 2;
	return ;
}

char	*get_expand(char *line, int *i, t_herdoc *herdoc)
{
	char	*val;

	val = NULL;
	(*i)++;
	if (ft_isdigit(line[*i]))
		return ((*i)++, NULL);
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		val = ft_strjoin(val, create_string(line[*i]));
		(*i)++;
	}
	return (get_exp(val, herdoc->env));
}

char	*herdoc_expand(char *line, t_herdoc *herdoc)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			skip_dollar(line, &i);
			if (line[i] == '$')
				s = ft_strjoin(s, get_expand(line, &i, herdoc));
		}
		else
			while (line[i] && line[i] != '$')
			{
				s = ft_strjoin(s, create_string(line[i]));
				i++;
			}
	}
	return (s);
}

t_herdoc	*init_herdoc(t_env **envp)
{
	t_herdoc	*herdoc;

	herdoc = gc_malloc(sizeof(t_herdoc), getter());
	memset(herdoc, 0, sizeof(t_herdoc));
	herdoc->env = envp;
	return (herdoc);
}

int	open_herd_file(t_herdoc *herdoc)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup("/tmp/herdoc_");
	while (1)
	{
		if (access(path, F_OK) != 0)
			break ;
		path = ft_strjoin(path, ft_itoa(i));
		i++;
	}
	herdoc->fd = open(path, O_CREAT | O_RDWR, 0644);
	return (herdoc->fd);
}

int	exit_failure(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

int	handel_herdoc(t_env **env, t_token *token, t_redir *redir)
{
	char	*line;

	redir->herdoc = init_herdoc(env);
	if (!redir->herdoc)
		return (EXIT_FAILURE);
	if (open_herd_file(redir->herdoc) < 0)
		return (exit_failure("open failed"));
	while (1)
	{
		line = readline("herdoc>");
		if (!line)
		{
			ft_putstr_fd("warning: here-document at line delimited by end-of-file\n",
				2);
			break ;
		}
		if (!ft_strcmp(line, token->value))
		{
			free(line);
			break ;
		}
		if (!has_quotes(token))
		{
			line = herdoc_expand(line, redir->herdoc);
			ft_putstr_fd(ft_strjoin(line, "\n"), redir->herdoc->fd);
		}
		else
		{
			ft_putstr_fd(ft_strjoin(line, "\n"), redir->herdoc->fd);
			free(line);
		}
	}
	return (EXIT_SUCCESS);
}

int	creat_red(t_redir **red_list, int type, t_token *token, t_lexer *lexer)
{
	t_redir	*redir;

	redir = gc_malloc(sizeof(t_redir), getter());
	redir->name = token->value;
	redir->type = type;
	redir->next = NULL;
	redir->herdoc = NULL;
	redir->fd_in = 0;
	redir->fd_out = 0;
	if (type == T_HERDOC)
	{
		if (handel_herdoc(lexer->env, token, redir) || !redir)
			return (EXIT_FAILURE);
	}
	if (lexer->error)
		return (EXIT_FAILURE);
	add_redir(red_list, redir);
	return (EXIT_SUCCESS);
}

void	print_listtt(t_command *token)
{
	int	i;

	while (token)
	{
		i = 0;
		printf("cmd: ");
		if (token->arg)
		{
			while (token->arg[i])
			{
				if (token->arg[i])
					printf("[%s] ", token->arg[i]);
				else
					printf("(null) ");
				i++;
			}
		}
		else
		{
			printf("(no args) ");
		}
		printf("\n");
		token = token->next_com;
	}
}

// int is_invalid(t_token *token)
// {
//     if(!token)
//         return(1);
//     return(0);
// }

void	*handle_redirection(t_command *cur_comd, t_token **token,
		t_lexer *lexer)
{
	int	red_type;

	red_type = (*token)->type;
	if ((*token)->next && is_word((*token)->next->type))
	{
		*token = (*token)->next;
		if (creat_red(&cur_comd->redir, red_type, *token, lexer))
			return (NULL);
	}
	else
		return (syntax_error());
	return (SUCCESS_PTR);
}

static void	end_of_command(t_command **cur_comd, int *f)
{
	if (*cur_comd)
		(*cur_comd)->arg[*f] = NULL;
	*cur_comd = NULL;
	*f = 0;
}

t_command	*init_comd(t_command *cur_comd, t_command **list, t_token *token)
{
	if (!cur_comd)
		return (new_comd(list, token));
	return (cur_comd);
}

t_command	*creat_comand_list(t_token *token, t_lexer *lexer)
{
	t_command	*list;
	t_command	*cur_comd;
	int			f;

	f = 0;
	list = NULL;
	cur_comd = NULL;
	while (token)
	{
		cur_comd = init_comd(cur_comd, &list, token);
		if (is_word(token->type))
			fill_arg(cur_comd, f++, token);
		else if (is_red(token->type))
			if (!handle_redirection(cur_comd, &token, lexer))
				return (NULL);
		if ((!token->next || token->type == T_PIPE) && cur_comd->arg)
			end_of_command(&cur_comd, &f);
		token = token->next;
	}
	if (lexer->error)
		return (NULL);
	print_listtt(list);
	return (list);
}

// t_command *creat_comand_list(t_token *token, t_lexer *lexer)
// {
//     t_command *list;
//     t_command *cur_comd;
//     int f;
//     int red_type;
//     f = 0;

//     cur_comd = NULL;
//     list = NULL;
//     while(token)
//     {
//         if (cur_comd == NULL)
//             cur_comd = new_comd(&list, token);
//         if(is_word(token->type))
//             fill_arg(cur_comd, f++, token);
//         else if(is_red(token->type))
//         {
//             red_type = token->type;
//             if(token->next && is_word(token->next->type))
//             {
//                 token = token->next;
//                 if(creat_red(&cur_comd->redir, red_type, token, lexer))
//                     return(NULL);
//             }
//             else
//                 return(syntax_error());
//         }
//         if((token->next == NULL || token->type == T_PIPE ) && cur_comd->arg)
//         {
//             cur_comd->arg[f] = NULL;
//             cur_comd = NULL;
//             f = 0;
//         }
//         token = token->next;
//     }
//     if(lexer->error)
//         return(NULL);
//     print_listtt(list);
//     return(list);
// }

t_command	*parser(t_lexer *lexer)
{
	if (parser_check(lexer->head))
		return (syntax_error());
	return (creat_comand_list(lexer->reel_head, lexer));
}