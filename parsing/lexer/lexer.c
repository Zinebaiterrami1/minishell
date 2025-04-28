/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/28 22:10:08 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mimi.h"

typedef struct s_lexer
{
    char c;
    char *line;
    int status_d;
    int status_s;
    int error;
    unsigned int i;
    t_token *head;
    size_t line_size;
    
}t_lexer;

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;
    lexer = gc_malloc(sizeof(t_lexer), getter());
    lexer->line = line;
    lexer->head = NULL;
    lexer->i = 0;
    lexer->c = line[lexer->i];
    lexer->line_size = ft_strlen(line);
    lexer->error = 0;
    lexer->status_d = 0;
    lexer->status_s = 0;
    return(lexer);
}

void lexer_skip_white(t_lexer *lexer)
{
    while(lexer->line[lexer->i] == ' ' || lexer->line[lexer->i] == '\t')
        lexer->i++;
    lexer->c = lexer->line[lexer->i];
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
    ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
    lexer->i = i + 1;
    return(set_token(token, s, T_S_COTS));/////////////////needs check with freind and create handel d
}

int has_exp(char *s)
{
    int  i;

    i = 0;
    while(s[i])
    {
        if(s[i] == '$' && ft_isalpha(s[i + 1]))
            return(1);
        i++;
    }
    return(0);
}

t_token *handel_d_quotes(t_lexer *lexer)
{
    t_token *token;
    int len;
    char *s;
    int i;
    
    i  = lexer->i;
    len = 0;
    lexer->status_s = 1;
    token = gc_malloc(sizeof(t_token), getter());
    while(lexer->line[i + 1] && lexer->line[++i] != '"')
        len++;
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
    lexer->i = i + 1;
    if(has_exp(s))
        return(set_token(token, s, T_EXP));
    return(set_token(token, s, T_D_COTS));/////////////////needs check with freind and create handel d
}

int is_special(char c)
{
    if (c == ' ' || c == '\t' || c == '\'' 
        || c == '"' || c == '|' || c == '&'
        || c == '>' || c == '<' || c == '\0')
        return(1);
    return(0);
}

t_token *handel_else(t_lexer *lexer)
{
    t_token *token;
    int len;
    char *s;
    int i;
    
    i  = lexer->i;
    len = 0;
    token = gc_malloc(sizeof(t_token), getter());
    while(lexer->line[i] && !is_special(lexer->line[i]))
    {
        len++;
        i++;
    }
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[lexer->i], len + 1);
    lexer->i = i;
    return(set_token(token, s, T_WORD));
}

t_token *pick_dollar(t_lexer *lexer, t_token *token)
{
    char *s;
    int len;
    int i;
    int u;

    u = 1;
    len = 0;
    lexer->i += 2;
    i = lexer->i;
    while(lexer->line[i] && lexer->line[i++] != '"')
        len++;
    s = gc_malloc(sizeof(char) * (len + 2), getter());
    s[0] = '$';
    while(u <= len)
    {
        s[u++] = lexer->line[lexer->i++];
    }
    s[u] = '\0';
    lexer->i += 1;
    return(set_token(token, s, T_WORD));
}

t_token *pick_singl_dollar(t_lexer *lexer, t_token *token)
{
    char *s;
    int len;
    int i;
    int u;

    u = 0;
    len = 0;
    lexer->i += 2;
    i = lexer->i;
    while(lexer->line[i] && lexer->line[i++] != '\'')
        len++;
    s = gc_malloc(sizeof(char) * (len + 1), getter());
    while(u < len)
    {
        s[u++] = lexer->line[lexer->i++];
    }
    s[u] = '\0';
    lexer->i += 1;
    return(set_token(token, s, T_WORD));
}

t_token *handel_expand(t_lexer *lexer, t_token *token)
{
    int i;
    int len;
    char *s;
    
    len = 0;
    i = lexer->i;
    while(lexer->line[i] && !is_special(lexer->line[i]))
    {
        len++;
        i++;
    }
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[lexer->i], len + 1);
    lexer->i = i;
    printf("i == %d lexer->i == %d \n", i, lexer->i);
    return(set_token(token, s, T_EXP));
}

void *skip(t_lexer *lexer)
{
    lexer->i += 1;
    while(!is_special(lexer->line[lexer->i]))
    {
        lexer->i++;
    }
    return(NULL);
}

t_token *handel_dollar(t_lexer *lexer)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    if(lexer->line[lexer->i + 1] == '\0')
        return(lexer->i++, set_token(token, "$", T_WORD));
    else if(isalpha(lexer->line[lexer->i + 1]) 
     || lexer->line[lexer->i + 1] == '_' 
     || lexer->line[lexer->i + 1] == '?')
        return(handel_expand(lexer, token));
    else if(lexer->line[lexer->i + 1] == '"')
        return(pick_dollar(lexer, token));
    else if(lexer->line[lexer->i + 1] == '\'')
        return(pick_singl_dollar(lexer, token));
    else if(lexer->line[lexer->i + 1] == '$')
        return(lexer->i += 2, NULL);
    else if(isalnum(lexer->line[lexer->i + 1]))
        return(skip(lexer));
    else
        return(handel_else(lexer));
    return(NULL);
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

void print_list(t_token *token)
{
    while(token)
    {
        printf("%s (%d) === ", token->value, token->type);
        token = token->next;
    }
    printf("\n");
}

void print_listt(t_garbage *token)
{
    while(token)
    {
        printf("%p === ", token->adress);
        token = token->next;
    }
    printf("\n");
}

int help(char *line, int *i)
{
    char quotes_char;
    int quotes_open;
    int exit;

    exit = 0;
    quotes_char = line[*i];
    (*i)++;
    quotes_open = 1;
    while(line[*i] && line[*i] != quotes_char)
        (*i)++;
    if(line[*i] == quotes_char)
    {
        quotes_open = 0;
        // (*i)++;
    }
    else 
        exit = 1;
    printf("%d\n", *i);
    return(exit);
}

int check(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(line[i] == '"' || line[i] == '\'')
            if(help(line, &i))
                return(1);
        if(line[i])
            i++;
    }
    return(0);
}

int syntax_error()
{
    printf("syntax error \n");
    return(1);
}

int lexer(char *line)
{
    t_lexer *lexer;
    t_token *token;
    

    if(check(line))
        return(syntax_error());
    lexer = init_lexer(line);
    while(lexer->i < lexer->line_size)
    {
        lexer_skip_white(lexer);
        token = get_next_token(lexer);
        if(token)
            adding_token(lexer, token);
        if(lexer->error)
            return(1);
        // printf("i mor skip white = %d\n", lexer->i);
    }
    print_list(lexer->head);
    free_all(getter());
    return(0);
}

int main()
{
    char *line;
    while(1)
    {
        line = readline("$minishell V2 ");
        if (!line)
            break;
        add_history(line);
        if(lexer(line) == 1)
        {
            free(line);
            continue;
        }
        free(line);
    }
    
}