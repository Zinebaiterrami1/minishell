/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/16 12:16:02 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_lexer *init_lexer(char *line)
// {
//     t_lexer *lexer;
//     lexer = gc_malloc(sizeof(t_lexer), getter());
//     lexer->line = line;
//     lexer->head = NULL;
//     lexer->reel_head = NULL;
//     lexer->i = 0;
//     lexer->c = line[lexer->i];
//     lexer->line_size = ft_strlen(line);
//     lexer->error = 0;
//     lexer->status_d = 0;
//     lexer->status_s = 0;
//     // lexer->head->space = 0;
//     return(lexer);
// }
t_lexer *init_lexer(char *line, t_env **env)
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
    lexer->env = env;
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
t_token *set_new_token(t_token *token, char *s, t_token *old_token, int separat_red)
{
    if(s)
        token->value = s;
    else
        token->value = old_token->value;
    if(separat_red)
        token->space = 1;
    else
        token->space = old_token->space;
    if(old_token->type == T_WORD && old_token->next && !token->space)
        token->type = old_token->next->type;
    else
        token->type = old_token->type;
    token->next = NULL;
    return(token);
}
t_token *handel_pipe(t_lexer *lexer)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    token->d_quotes = 0;
    token->space = 1;
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
    token->d_quotes = 0;
    token->space = 1;
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
    token->d_quotes = 0;
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
        if(s[j] == '$' && s[j + 1] && s[j + 1] == '$')
            j += 2;
        if(j < i)
            str = ft_strjoin(str, create_string(s[j]));
        j++;
    }
            // printf("______%s________\n",str);
    return(str);
}

// char *get_next_word(char *str, int *i)
// {
//     char *s;
//     int j;
    
//     s = NULL;
//     j = 0;
//     while(str[*i] && str[*i + 1])
//     {
//         if (str[*i] == '$' && str[*i + 1] == '$')
//             (*i) += 2;
//     }
//     while(str[*i] && str[*i] != ' ' && str[*i] != '\t')
//     {
//         s = ft_strjoin(s, create_string(str[*i]));
//         (*i)++;
//     }
//     return(s);
// }

int has_dollar(char **s)
{
    int  i;
    int count;
    char *str;
    
    str = *s;
    count = 0;
    i = 0;
    // printf("hasdollar\n");
    while(str[i])
    {
        if(str[i] == '$')
        {
            while(str[i] && str[i] == '$')
            {
                count++;
                i++;
            }
        }
        if((str[i] && (ft_isalpha(str[i]) || str[i] == '_') && count) || !str[i])
        {
            *s = ft_strjoin(get_string(*s, i) , &str[i]);
            
            return(1);
        }
        if(str[i])
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
    // printf("s ___________________________________ %s\n", s);
    if(has_dollar(&s))
            return(set_token(token, s, T_EXP));
    return(set_token(token, s, T_D_COTS));/////////////////needs check with freind and create handel d
}

int is_special(char c)
{
    if (c == ' ' || c == '\t' || c == '\'' 
        || c == '"' || c == '|'
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
    token->d_quotes = 0;
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
	if(has_dollar(&s))
	    return(set_token(token, s, T_EXP));
    return(set_token(token, s, T_WORD));
}

t_token *pick_d_quotes_dollar(t_lexer *lexer, t_token *token)
{
    char *s;
    int len;
    int i;
    int u;

    u = 0;
    len = 0;
    lexer->i += 2;
    i = lexer->i;
    while(lexer->line[i] && lexer->line[i++] != '"')
        len++;
    if(lexer->line[i] && lexer->line[i] && is_space(lexer->line[i]))
        token->space = 1;
    s = gc_malloc(sizeof(char) * (len + 1), getter());
    // s[0] = '$';
    while(u < len)
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
    if(lexer->line[i] && lexer->line[i] && is_space(lexer->line[i]))
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
        if(lexer->line[i] && is_space(lexer->line[i]))
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
    token->d_quotes = 0;
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
    else if(isdigit(lexer->line[lexer->i + 1]))
        return(lexer->i += 2, NULL);
    else
        return(handel_else(lexer));
    return(NULL);
}

t_token *dilim_helper()
{
    t_token *token;

    token = gc_malloc(sizeof(t_token), getter());
    token->d_quotes = 0;
    token->space = 0;
    token->type = T_WORD;
    return(token);
}

static int is_redir(char c)
{
    if (c == '>' || c == '<')
        return(1);
    return(0);
}

t_token *handel_dilim(t_lexer *lexer)
{
    t_token *token;
    char *s;
    int i;
    
    i  = lexer->i;
    s = ft_strdup("");
    token = dilim_helper();
    while(lexer->line[i] && !is_space(lexer->line[i]) 
    && !is_redir(lexer->line[i]))
    {
        if(lexer->line[i] == '"' || lexer->line[i] == '\'')
        {
            token->type = T_S_COTS;
            token->d_quotes = 1;
        }
        else
            s = ft_strjoin(s, create_string(lexer->line[i]));
        // if(lexer->line[i] && !is_space(lexer->line[i]))
        i++;
    }
    if(lexer->line[i] && is_space(lexer->line[i]))
        token->space = 1;
    lexer->i = i;
    // printf("s_____________________%s___\n", s);
    return(set_token(token, s, token->type));
}

t_token *handel_word(t_lexer *lexer)
{
    t_token *last;

    last = ft_lstlast(lexer->head);
    if(last && last->type == T_HERDOC)
        return(handel_dilim(lexer));
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
    if(last && !last->space && is_word(token->type))
    {
        last->value = ft_strjoin(last->value, token->value);
        last->space = token->space;
        if(last->type == T_WORD)
            last->type = token->type;
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

char *get_exp(char *var, t_env **env)
{
    // t_env *env_list;
    
    // env_list = split_env(init_env(env));
    char *s;
    s = get_env_value(*env, var);
    return(s);
}

char *should_not_be_expanded(char **val)
{
    int i;

    i = 0;
    while(*val[i] && *val[i] == '$')
    {
        // (*val)++;
        i++;
    }
    if (i % 2 == 0)
        return(ft_strdup(""));
    else if(ft_isdigit(**val))
    {
        (*val)++;
        return(ft_strdup(""));
    }
    else
        return(NULL);
    
}
    // while(token_val)
    // {
    //     printf("is exp val____________ = %s\n", *token_val);
    //     if(**token_val == '$')
    //         (*token_val)++;
    //     if(ft_isalpha(**token_val) || **token_val == '_')
    //     {
    //         while(**token_val == '_' || ft_isalnum(**token_val))
    //         {
    //             s = ft_strjoin(s, create_string(**token_val));
    //             (*token_val)++;
    //         }
            
    //         get_val = get_exp(s, env);
    //         if(get_val)
    //             ret = ft_strjoin(ret, get_val);
    //         else
    //             ret = ft_strjoin(ret, ft_strdup("$"));
    //         printf("is exp val____________ = %s\n", ret);
    //         s = NULL;
    //     }
    // }
    // return(ret);
    

    


    


    
    
    


void append_token(t_token *old_token, char *s, t_lexer *lexer, int flag)
{
    t_token *token;
    
    token = gc_malloc(sizeof(t_token), getter());
    set_new_token(token, s, old_token, flag);
    printf("append_token->val ____________________ %s\n", token->value);
    adding_new_token(lexer,token);
}
void skip_white_spaces(char *s, int *i)
{
    while(s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
        (*i)++;
}
char *befor_space(char *s, int *i)
{
    char *str;

    str = NULL;
    skip_white_spaces(s, i);
    while(s[*i] && s[*i] != ' ' && s[*i] != '\t')
    {
        str = ft_strjoin(str, create_string(s[*i]));
        (*i)++;
    }
    printf("before space = ________%s\n", str);
    return(str);
}
char *after_space(char *s, int *i)
{
    char *str;

    str = NULL;
    skip_white_spaces(s, i);
    while(s[*i] && s[*i] != ' ' && s[*i] != '\t')
    {
        str = ft_strjoin(str, create_string(s[*i]));
        (*i)++;
    }
    printf("---- after space %s\n", str);
    return(str);
}

/*void creat_new_token_exp(t_lexer *lexer, t_token *token,char **env)
{
    char *s;
    char *val;

    s = NULL;
    if(!token || !token->value)
        return;
    while(token && *token->value)
    {
        if(token && *token->value && !ft_strncmp((const char *)(token->value), "$", 1))
        {
            printf("---   token   %s\n",token->value);
            val = is_exp(&token->value, env);
            printf("---  val  %s\n", val);
            if(!has_space(val))
            {
                s = ft_strjoin(s, val);
                printf("---   s    %s\n", s);
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
    }
    append_token(token, s, lexer);
}*/

int num_of_word(char *str)
{
    int count = 0;
    int in_word = 0;

    while (*str)
    {
        if (is_space(*str))
            in_word = 0;
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

char *is_exp(char **token_val, t_env **env)
{
    char *s;
    char *ret;
    // char *get_val;

    s = ft_strdup("");
    ret = ft_strdup("");
    printf("is exp val____________ = %s\n", *token_val);
    // if(should_not_be_expanded(token_val))
    // {
    //     printf("s_should not be exp_________________ %s\n", *token_val);
    //     return(s);   
    // }


    while(**token_val)
    {
        if(**token_val == '$')
        {
            (*token_val)++;
            if(!*token_val)
                break;
            while(**token_val == '$')
                (*token_val)++;
            if(ft_isalpha(**token_val) || **token_val == '_')
            {
                while(**token_val == '_' || ft_isalnum(**token_val))
                {
                    s = ft_strjoin(s, create_string(**token_val));
                    (*token_val)++;
                }
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s\n",*token_val);

                ret = ft_strjoin(ret, get_exp(s, env));
                s = NULL;
            }
            else if(**token_val == '?')
                ret = ft_strjoin(ret, ft_itoa(g_exit_status));
        }
        else   
        {
            ret = ft_strjoin(ret, create_string(**token_val));
            (*token_val)++;
        }
        
    }
    return(ret);

    
    // printf("is exp val____________ = %s\n", *token_val);
    
    // if(ft_isalpha(**token_val) || **token_val == '_')
    // {
    //     while(**token_val == '_' || ft_isalnum(**token_val))
    //     {
    //         s = ft_strjoin(s, create_string(**token_val));
    //         (*token_val)++;
    //     }
    //     ret = get_exp(s, env);
    //     printf("is exp return____________ = %s\n", ret);
    //     if(ret)
    //         return(ret);
    //     return(NULL);
    // }
    // return(NULL); 
}

void *creat_new_token_exp(t_lexer *lexer, t_token *token, t_env **env)
{
    char *s;
    char *val;
    int i;
    char **splited;

    i = 0;
    s = NULL;
    if(!token || !token->value)
        return (NULL);
    // ft_display_env(*env, NULL);
    while(token && *token->value)
    {
        if(token && *token->value && !ft_strncmp((const char *)(token->value), "$", 1))
        {
            printf("token->val ______________ %s\n",token->value);
            val = ft_strjoin(s, is_exp(&token->value, env));
            if(val && num_of_word(val) > 1 &&(ft_lstlast(lexer->reel_head)) 
                && (ft_lstlast(lexer->reel_head)->type == T_RED_OUT 
                || ft_lstlast(lexer->reel_head)->type == T_RED_OUT_APEND 
                || ft_lstlast(lexer->reel_head)->type == T_RED_IN))
                {
                    lexer->error = 1;
                    return(ft_putstr_fd("ambiguous redirect\n", 2), SUCCESS_PTR);
                }
            printf("value_________________ ___ %s\n", val);
            if(val && has_space(val) && !token->d_quotes)
            {
                splited = ft_split(val, ' ');
                while(splited[i])
                {
                    append_token(token, splited[i], lexer, 1);
                    i++;
                }
            }
            else
            {
                append_token(token, val, lexer, 0);
            }
        }
        else
        {
            s = ft_strjoin(s, create_string(*token->value));
            token->value++;
        }
    }
    return(NULL);
}
    //         while(val && (unsigned int)i < ft_strlen(val))
    //         {
    //             if(!has_space(val) || token->d_quotes)//has_space not numofword
    //             {
    //                 s = ft_strjoin(s, val);
    //                 printf("_______ s __%s_______val __ %s\n",s, val);
    //                 break;
    //             }
    //             else
    //             {
    //                 s = ft_strjoin(s, befor_space(val, &i));
    //                 printf("i = _______ %d\n", i);
    //                 append_token(token, s, lexer, 1);
    //                 s = NULL;
    //             }
    //             // break;
    //         }
    //     }
    //     else if(*token->value && ft_strncmp((const char *)(token->value), "$", 1))
    //     {
    //         printf("salamo3alikom\n");
    //         s = ft_strjoin(s, create_string(*token->value));
    //         token->value++;
    //     }
    //     // break;
    // }
    // if(s)
    //     append_token(token, s, lexer, 0);
    // return(NULL);
// }



int reel_list(t_lexer *lexer, t_env **env)
{
    t_token *token;
    // t_token *last;

    token = lexer->head;
    // last = ft_lstlast(lexer->reel_head);
    while(token)
    {
        if(token->type == T_EXP)
            creat_new_token_exp(lexer, token, env);
        else
            append_token(token, NULL, lexer, 0);
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


t_command *parsing(char *line, t_env **env)
{
    t_lexer *lexer;
    t_token *token;
    
    (void)env;
    if(check(line))
        return(syntax_error());
    lexer = init_lexer(line, env);
    while(lexer->i < lexer->line_size)
    {
        lexer_skip_white(lexer);
        if(lexer->line[lexer->i] == '\n' || lexer->line[lexer->i] == '\0')
            break;
        token = get_next_token(lexer);
        if(token)
            adding_token(lexer, token);
        if(lexer->error)
            return(NULL);
    }
    print_list(lexer->head);
    reel_list(lexer, env);
    print_list2(lexer->reel_head);
    // free_all(getter());
    return( parser(lexer));
}

#include <stdio.h>

void	print_test(t_env *head)
{
	t_env *current = head;

	while (current)
	{
		if (current->env_value)
			printf("%s=%s\n", current->env_key, current->env_value);
		else
			printf("%s\n", current->env_key);
		current = current->next;
	}
}

void *minishell(char *line, t_env **env_lst)
{
    int (stdin), (stdout);

    stdin = dup(STDIN_FILENO);
    stdout = dup(STDOUT_FILENO);
    t_command *list;
    
    list = parsing(line, env_lst);
    if(!list)
        return(syntax_error());
    // ft_display_env(*env_lst, list);
    if(is_buitins(list) && ft_lstsizee(list) == 1)
        execute_buitlins(env_lst, list);
    else if(!is_buitins(list) && ft_lstsizee(list) == 1)
        execute_externals(list, *env_lst);
    else if (ft_lstsizee(list) > 1)
        if(!multiple_pipes(env_lst, list))
            return(NULL);
    dup2(stdin, STDIN_FILENO);
    dup2(stdout, STDOUT_FILENO);
    close(stdin);
    close(stdout);
    return(list);
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

// int main(int argc, char **argv, char **env)
// {
//     char *line;

//     (void) argc;
//     (void) argv;
//     while(1)
//     {
//         line = readline("$minishell V2 ");
//         if (!line)
//             break;
//         if (line[0] == '\0')
//             continue;
//         add_history(line);
//         if(minishell(line, env))
//         {
//             free(line);
//             continue;
//         }
//         free(line);
//         // if(lexer(line) == 1)
//         // {
//         //     free(line);
//         //     syntax_error();
//         //     continue;
//         // }
//     }
// }
