/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 00:40:20 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//"$$$HOME"

int	parser_check(t_token *token)
{
	if (token && token->type == T_PIPE)
		return (EXIT_FAILURE);
	while (token)
	{
		if (token->type == T_PIPE && (token->next == NULL
				|| token->next->type == T_PIPE || *(token->next->value) == '('
				|| *(token->next->value) == ')'))
			return (EXIT_FAILURE);
		token = token->next;
	}
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

t_command	*parser(t_lexer *lexer)
{
	if (parser_check(lexer->head))
		return (syntax_error(1));
	return (creat_comand_list(lexer->reel_head, lexer));
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
// 				{
// 					printf("salam\n");
//                     return(NULL);
// 				}
//             }
//             else
//                 return(syntax_error(2));
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