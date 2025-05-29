/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/05/29 17:40:02 by nel-khad         ###   ########.fr       */
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
    // lexer->head->space = 0;
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
t_token *set_new_token(t_token *token, char *s, t_token *old_token)
{
    token->type = old_token->type;
    if(s)
        token->value = s;
    else
        token->value = old_token->value;
    token->space = old_token->space;
    printf("space %d\n", token->space);
    token->next = NULL;
    return(token);
}
t_token *handel_pipe(t_lexer *lexer)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    token->space = 0;
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
    token->space = 0;
    if(lexer->line[lexer->i] == '>')
        return(handel_redir_out(token, lexer));
    else if(lexer->line[lexer->i] == '<')
        return(handel_redir_in(token, lexer));
    return(NULL);
}

int is_space(char c)
{
    if(c == ' ' || c == '\t')
        return(1);
    return(0);
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
    token->space = 0;
    while(lexer->line[i + 1] && lexer->line[++i] != '\'')
        len++;
    if(lexer->line[i] && lexer->line[i + 1] && is_space(lexer->line[i + 1]))
        token->space = 1;
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
    lexer->i = i + 1;
    return(set_token(token, s, T_S_COTS));/////////////////needs check with freind and create handel d
}

// int valid_exp(char *s)
// {
//     int i;
    
//     i = 0;
//     if(s[0] != '_' && !ft_isalpha(s[0]))
//         return(0);
//     while(s[i])
//     {
    //         if(s[])
    //     }
    // }
char *create_string(char c)
{
    char *tmp;

    if(c == '\0')
        tmp = ft_strdup("");
    tmp = gc_malloc(sizeof(char) * 2, getter());
    tmp[0] = c;
    tmp[1] = '\0';
    return(tmp);
}

char *get_string(char *s, int i)
{
    int j;
    char *str;
    
    j = 0;
    str = NULL;
    
    while(j < i)
    {
        str = ft_strjoin(str, create_string(s[j]));
        j++;
    }
    return(str);
}

int has_dollar(char **s)
{
    int  i;
    int count;
    
    char *str;
    str = *s;
    count = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == '$')
            while(str[i] && str[i] == '$')
            {
                count++;
                i++;
            }
        if((ft_isalpha(str[i]) || str[i] == '_') && count % 2 != 0)
        {
            *s = ft_strjoin(get_string(*s, i) , ft_strjoin("$", &str[i]));
            return(1);
        }
        else if (count && count % 2 == 0)
        {
            *s = ft_strjoin(get_string(*s, i) , ft_strjoin("", &str[i]));
            return(0);
        }
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
    token->space = 0;
    token->d_quotes = 1;
    while(lexer->line[i + 1] && lexer->line[++i] != '"')
        len++;
    if(lexer->line[i] && lexer->line[i + 1] && is_space(lexer->line[i + 1]))
        token->space = 1;
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[++lexer->i], len + 1);
    lexer->i = i + 1;
    printf("s === %s\n", s);
    if(has_dollar(&s))
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
    token->space = 0;
    while(lexer->line[i] && !is_special(lexer->line[i]))
    {
        len++;
        i++;
    }
    if(lexer->line[i] && is_space(lexer->line[i]))
        token->space = 1;
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[lexer->i], len + 1);
    lexer->i = i;
    return(set_token(token, s, T_WORD));
}

t_token *pick_d_quotes_dollar(t_lexer *lexer, t_token *token)
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
    if(lexer->line[i] && lexer->line[i + 1] && is_space(lexer->line[i + 1]))
        token->space = 1;
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

t_token *pick_s_quotes_dollar(t_lexer *lexer, t_token *token)
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
    if(lexer->line[i] && lexer->line[i + 1] && is_space(lexer->line[i + 1]))
        token->space = 1;
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
    if(lexer->line[i])
    {
        if(lexer->line[i + 1] && is_space(lexer->line[i + 1]))
            token->space = 1;
    }
    s = gc_malloc(sizeof(char ) * (len + 1), getter());
    ft_strlcpy(s, &lexer->line[lexer->i], len + 1);
    lexer->i = i;
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
    token->space = 0;
    if(lexer->line[lexer->i + 1] == '\0')
        return(lexer->i++, set_token(token, "$", T_WORD));
    else if(isalpha(lexer->line[lexer->i + 1]) 
     || lexer->line[lexer->i + 1] == '_' 
     || lexer->line[lexer->i + 1] == '?')
        return(handel_expand(lexer, token));
    else if(lexer->line[lexer->i + 1] == '"')
        return(pick_d_quotes_dollar(lexer, token));
    else if(lexer->line[lexer->i + 1] == '\'')
        return(pick_s_quotes_dollar(lexer, token));
    else if(lexer->line[lexer->i + 1] == '$')
        return(lexer->i += 2, NULL);
    else if(isalnum(lexer->line[lexer->i + 1]))
        return(lexer->i += 2, NULL);
    else
        return(handel_else(lexer));
    return(NULL);
}

t_token *handel_word(t_lexer *lexer)
{
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

t_token *skip_tokens(t_token *token)
{
    while(token && !token->space)
    {
        token = token->next;
    }
    return(token);
}

int len_count(char *s, char c)
{
    int i;
    int len;
    
    len = 0;
    i = 0;
    while(s[i] && s[i] != c)
    {
        if(s[i] != c && !isalpha(s[i]))
            return(len);
        len++;
        i++;
    }
    return(len);
}

void *adding_new_token(t_lexer *lexer, t_token *token)
{
    t_token *last;
    
    if (!token)
        return(NULL);
    last = ft_lstlast(lexer->reel_head);
    // if (last)
    //     printf("===============%s\n",last->value);
    if(last && !last->space)
    {
        last->value = ft_strjoin(last->value, token->value);
        last->space = token->space;
        printf("last............................ = %s - %d\n", last->value, last->space);

    }
    else
        ft_lstadd_back(&lexer->reel_head, token);
    return(NULL);
}

int has_space(char *s)
{
    int i;
    
    if(!s)
        return(0);
    i = 0;
    while(s[i++])
    {
        if(s[i] == ' ' || s[i] == '\t')
            return(1);
    }
    return(0);
}

char *get_exp(char *var, char **env)
{
    t_env *env_list;
    
    env_list = split_env(init_env(env));
    return(get_env_value(env_list, var));
}

char *is_exp(char **val, char **env)
{
    char *s;
    char *ret;
    
    s = ft_strdup("");
    while(**val == '$')
        (*val)++;
    if(!ft_isalnum(**val))
    {
        (*val)++;
        return(s);
    }
    else if(ft_isalpha(**val) || **val == '_')
    {
        while(ft_isalpha(**val) || **val == '_' || ft_isalnum(**val))
        {
            s = ft_strjoin(s, create_string(**val));
            (*val)++;
        }
        ret = get_exp(s, env);
        if(ret)
            return(ret);
        return(ft_strjoin("$", s));
    }
    else
        return("$");
}

void append_token(t_token *old_token, char *s, t_lexer *lexer)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    set_new_token(token, s, old_token );
    adding_new_token(lexer,token);
}

char *befor_space(char *s)
{
    int i;
    char *str;

    i = 0;
    while(s[i] && s[i] != ' ' && s[i] != '\t')
    {
        str = ft_strjoin(str, create_string(s[i]));
        i++;
    }
    return(str);
}
char *after_space(char *s, t_token *token)
{
    int i;
    char *str;

    i = 0;
    while(s[i] && s[i] != ' ' && s[i] != '\t')
        i++;
    if(!token->d_quotes)
        while(s[i] == ' ' || s[i] == '\t')
            i++;
    while(s[i])
    {
        str = ft_strjoin(str, create_string(s[i]));
        i++;
    }
    return(str);
}

void creat_new_token_exp(t_lexer *lexer, t_token *token,char **env)
{
    char *s;
    char *val;

    s = NULL;
    if(!token || !token->value)
        return;
    while(token && *token->value)
    {
        // printf("%c\n", *token->value);
        if(token && *token->value && !ft_strncmp((const char *)(token->value), "$", 1))
        {
            printf("---%s\n",token->value);
            val = is_exp(&token->value, env);
            printf("---%s\n", val);
            if(!has_space(val))
            {
                s = ft_strjoin(s, val);
                printf("---%s\n", s);
                // append_token(token, s, lexer);
            }
            else
            {
                s = ft_strjoin(s, befor_space(val));
                append_token(token, s, lexer);
                s = ft_strdup(after_space(val, token));
            }
        }
        else if(*token->value)
        {
            s = ft_strjoin(s, create_string(*token->value));
            if(*token->value)
                token->value++;
        }
        printf("***************%s\n", s);
    }
    append_token(token, s, lexer);
}

















// void creat_new_token_exp(t_lexer *lexer, t_token *token)
// {
//     char *s;
//     char *val;
//     // char *pre_s;
//     int len;

//     printf("ana create new token exp\n");
//     s = token->value;
//     if(*s == '$')
//     {
//         while(*s == '$')
//             s++;
//         if(!ft_isalnum(*s))
//         {
//             s++;
//             // pre_s = fill_pre_s(s);
//             // creat_new_token(lexer, token);//join with prev if space = 0 / add to the list;
//         }
//         else if(ft_isalpha(*s) || *s == '_' && valid_exp(s))
//         {
//             //len
//             len = len_count(s,'_');
            
//             //fill
//             val = gc_malloc(sizeof(char) * (len + 1), getter());
//             ft_strlcpy(val, s, len + 1);
//             printf("val = %s\n", val);
//             // expand new_token->value = expand
//             if(s[len] != '\0')
//                 // new_token->value = join_strings(new_token->v, s[len]);
//         }
//         else
//             creat_new_token(lexer, token);
//     }
//     // else
//     //     pre_s = fill_pre_s(s);
    
// }

// void creat_new_token(t_lexer *lexer, t_token *token)
// {
//     t_token *new;

//     printf("ana create new token\n");
//     new = gc_malloc(sizeof(t_token), getter());
//     adding_new_token(lexer, set_new_token(new, token));
//     return;    
// }

int reel_list(t_lexer *lexer, char **env)
{
    t_token *token;

    token = lexer->head;
    printf("%s\n", token->value);
    while(token)
    {
        if(token->type == T_EXP)
            creat_new_token_exp(lexer, token, env);
        else
            append_token(token, NULL, lexer);
        token = token->next;
    }
    return(0);
}



void print_list(t_token *token)
{
    printf("token list : ");
    while(token)
    {
        printf("%s (%d) [%d] --> ", token->value, token->type, token->space);
        token = token->next;
    }
    printf("\n");
}

void print_list2(t_token *token)
{
    printf("token list222 : ");
    while(token)
    {
        printf("%s (%d) [%d] --> ", token->value, token->type, token->space);
        token = token->next;
    }
    printf("\n");
}

int parsing(char *line, char **env)
{
    t_lexer *lexer;
    t_token *token;
    
    if(check(line))
        return(syntax_error());
    lexer = init_lexer(line);
    while(lexer->i < lexer->line_size)
    {
        lexer_skip_white(lexer);
        if(lexer->line[lexer->i] == '\n' || lexer->line[lexer->i] == '\0')
            break;
        token = get_next_token(lexer);
        if(token)
            adding_token(lexer, token);
        if(lexer->error)
            return(1);
    }
    reel_list(lexer, env);
    print_list(lexer->head);
    print_list2(lexer->reel_head);
    parser(lexer);
    free_all(getter());
    return(0);
}


int minishell(char *line, char **env)
{
    if(parsing(line, env))
        return(syntax_error());
    return(0);
}

int main(int argc, char **argv, char **env)
{
    char *line;

    (void) argc;
    (void) argv;
    while(1)
    {
        line = readline("$minishell V2 ");
        if (line[0] == '\0')
            continue;
        add_history(line);
        if(minishell(line, env))
        {
            free(line);
            continue;
        }
        free(line);
        // if(lexer(line) == 1)
        // {
        //     free(line);
        //     syntax_error();
        //     continue;
        // }
    }
}
