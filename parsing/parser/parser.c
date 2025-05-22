/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/05/22 18:55:52 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mimi.h"
//"$$$HOME"

int is_word(t_token_type type)
{
    if(type == T_WORD || type == T_D_COTS
        || type == T_EXP || type == T_S_COTS)
        return(1);
    return(0);
}

int parser_check(t_token *token)
{
    if(token->type == T_PIPE)
        return(EXIT_FAILURE);
    while(token)
    {
        if (token->type == T_PIPE 
        && (token->next == NULL || token->next->type == T_PIPE  || *(token->next->value) == '('  || *(token->next->value) == ')' ))
            return(EXIT_FAILURE);
        if(token->type == T_RED_IN || token->type == T_RED_OUT 
        || token->type == T_RED_IN || token->type == T_HERDOC)
        {
            if (token->next == NULL || !is_word(token->next->type))
            return(EXIT_FAILURE);
        }
        token = token->next;
    }
    return(EXIT_SUCCESS);
}

void *parser_error()
{
    printf("syntax error\n");
    // g_ext_status = 2;
    return(NULL);
}

int is_red(t_token_type type)
{
    if (type == T_RED_OUT || type == T_RED_IN 
    || type == T_RED_OUT_APEND || type == T_HERDOC)
        return(1);
    return(0);
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

void add_command(t_command **list, t_command *new)
{
	t_command   *ptr;

	if (new == NULL || !list)
        return ;
    ptr = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while(ptr->next_com)
    {
        ptr = ptr->next_com;
    }
	if (ptr)
		ptr->next_com = new;
	return;
}

t_command *new_comd(t_command **list, t_token *token)
{
    t_command *comd;
    t_token *cur;
    int count;
    
    count = 0;
    cur = token;
    comd = gc_malloc(sizeof(t_command) , getter());
    while (cur && is_word(cur->type))
    {
        count++;
        cur = cur->next;
    }
    printf("count = %d\n", count);
    comd->arg = gc_malloc(sizeof(char *) * (count + 1), getter());
    comd->next_com = NULL;
    comd->redir = NULL;
    add_command(list, comd);
    if(comd)
        return(comd);
    return(NULL);
}


void fill_arg(t_command *comd, int f, t_token *token)
{
    comd->arg[f] = gc_strdup(token->value);
}

void add_redir(t_redir **list, t_redir *new)
{
    t_redir   *ptr;
    
	if (new == NULL || !list)
    return ;
    ptr = *list;
	if (*list == NULL)
	{
        *list = new;
		return ;
	}
	while(ptr->next)
    {
        ptr = ptr->next;
    }
	if (ptr)
    ptr->next = new;
	return;
}

void creat_red(t_redir **red_list, int var, t_token *token)
{
    t_redir *redir;
    
    redir = gc_malloc(sizeof(t_redir), getter());
    redir->name = token->value;
    redir->type = var;
    redir->next = NULL;
    add_redir(red_list, redir);
}

void print_listtt(t_command *token)
{
    while (token)
    {
        int i = 0;
        printf("cmd: ");
        while (token->arg[i])
        {
            printf("arg = [%s] \n", token->arg[i]);
            if(token->redir && token->redir->name)
                printf("file name : %s\n",token->redir->name);
            i++;
        }
        token = token->next_com;
    }
    printf("\n");
}

int is_invalid(t_token *token)
{
    if(!ft_strncmp(token->value, "", 1))
        return(1);
    return(0);
}

t_command *creat_comand_list(t_token *token)
{
    t_command *list;
    t_command *cur_comd;
    int f;
    int red_type;
    f = 0;
    
    cur_comd = NULL;
    list = NULL;
    while(token)
    {
        if (cur_comd == NULL)
            cur_comd = new_comd(&list, token);//allocate and append command
        if(is_invalid(token) && token->next)
            token = token->next;
        if(is_word(token->type))
        {
            fill_arg(cur_comd, f++, token);
        }
        else if(is_red(token->type))
        {
            red_type = token->type;
            if(token->next && is_word(token->next->type))
            {
                token = token->next;
                creat_red(&cur_comd->redir, red_type, token);//allocate and append;//check if token->next is word
            }
            else
                return(parser_error());
        }
        if(token->next == NULL || token->type == T_PIPE)
        {
            cur_comd->arg[f] = NULL;
            cur_comd = NULL;
            f = 0;
        }
        token = token->next;
    }
    print_listtt(list);
    return(list);
}


// t_command *creat_comand_list(t_token **token)
// {
//     t_command *list;
//     t_command *cur_comd;
    
    
// }

t_command *parser(t_lexer *lexer)
{
    if(parser_check(lexer->head))
    return(parser_error());
    return(creat_comand_list(lexer->head));
}