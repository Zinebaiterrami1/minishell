/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/03 21:33:47 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mimi.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;
    lexer = gc_malloc(sizeof(t_lexer), getter());
    lexer->line = line;
    lexer->head = NULL;
    lexer->reel_head = NULL;
    lexer->i = 0;
    lexer->c = line[lexer->i];
    lexer->line_size = ft_strlen(line);
    lexer->error = 0;
    lexer->status_d = 0;
    lexer->status_s = 0;
    lexer->head->space = 0;
    return(lexer);
}

void lexer_skip_white(t_lexer *lexer)
{
    while( lexer->line[lexer->i] == ' ' || lexer->line[lexer->i] == '\t')
        lexer->i++;
    // lexer->c = lexer->line[lexer->i];
}

t_token *set_token(t_token *token, char *cmd, int type)
{
    token->type = type;
    token->value = cmd;
    token->next = NULL;
    return(token);
}

t_token *handel_pipe(t_lexer *lexer)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    lexer->i++;
    return(set_token(token, "|", T_PIPE));
}

t_token *handel_redir_out(t_token *token, t_lexer *lexer)
{
    if(lexer->line[lexer->i+1] == '>')
        return(lexer->i += 2, set_token(token, ">>", T_RED_OUT_APEND));
    else 
        return(lexer->i += 1, set_token(token, ">", T_RED_OUT));
}

t_token *handel_redir_in(t_token *token, t_lexer *lexer)
{
    if(lexer->line[lexer->i+1] == '<')
        return(lexer->i += 2, set_token(token, "<<", T_HERDOC));
    else 
        return(lexer->i += 1, set_token(token, "<", T_RED_IN));
}

t_token *handel_redir(t_lexer *lexer)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    if(lexer->line[lexer->i] == '>')
        return(handel_redir_out(token, lexer));
    else if(lexer->line[lexer->i] == '<')
        return(handel_redir_in(token, lexer));
    return(NULL);
}

char *next_sring(t_lexer *lexer, int i)
{
    
}

t_token *handel_s_quotes(t_lexer *lexer)
{
    t_token *token;
    int len;
    char *s;
    int i;
    
    i  = lexer->i;
    len = 0;
    lexer->status_s = 1;
    token = gc_malloc(sizeof(t_token), getter());
    while(lexer->line[i + 1] && lexer->line[++i] != '\'')
        len++;
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    while(!is_special(lexer->line[i]))
    {
        //ading next ccaracters intel  
    }
    ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
    s = ft_strjoin(s, next_string(lexer, i));
    lexer->i = i + 1;
    return(set_token(token, s, T_S_COTS));/////////////////needs check with freind and create handel d
}

t_token *handel_word(t_lexer *lexer)
{
    printf("ana f handel_word\n");
    if(lexer->line[lexer->i] == '\'')
        return(handel_s_quotes(lexer));
    else if(lexer->line[lexer->i] == '"')
        return(handel_d_quotes(lexer));
    else if(lexer->line[lexer->i] == '$')
        return(handel_dollar(lexer));
    else if(lexer->line[lexer->i] == '&')
        return(lexer->error = 1, NULL);
    else
        return(handel_else(lexer));
    return(NULL);
}

t_token *get_next_token(t_lexer *lexer)
{
    while(lexer->i < lexer->line_size && lexer->line[lexer->i])///////////////
    {
        if(lexer->i == lexer->line_size)
            return(NULL);
        lexer_skip_white(lexer);
        if(lexer->line[lexer->i] == '|')
            return(handel_pipe(lexer));
        else if(lexer->line[lexer->i] == '>' || lexer->line[lexer->i] == '<')
            return(handel_redir(lexer));
        else
            return(handel_word(lexer));
    }
    // lexer->error = 1;
    return(NULL);
}

void *adding_token(t_lexer *lexer, t_token *token)
{
    if (!token)
        return(NULL);
    ft_lstadd_back(&lexer->head, token);
    return(NULL);
}


// int lexer(char *line)
// {
//     t_lexer *lexer;
//     t_token *token;
    
//     if(check(line))
//         return(syntax_error());
//     lexer = init_lexer(line);
//     while(lexer->i < lexer->line_size)
//     {
//         lexer_skip_white(lexer);
//         if(lexer->line[lexer->i] == '\n' || lexer->line[lexer->i] == '\0')
//             return(1);
//         token = get_next_token(lexer);
//         if(token)
//             adding_token(lexer, token);
//         if(lexer->error)
//             return(1);
//     }
//     print_list(lexer->head);
//     parser(lexer);
//     free_all(getter());
//     return(0);
// }

// int main()
// {
//     char *line;
//     while(1)
//     {
//         line = readline("$minishell V3 ");
//         if (line[0] == '\0')
//             continue;
//         add_history(line);
//         if(lexer(line) == 1)
//         {
//             free(line);
//             syntax_error();
//             continue;
//         }
//         free(line);
//     }
// }