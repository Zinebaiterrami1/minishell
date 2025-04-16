/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:13:02 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/16 19:33:22 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mimi.h"

void skip_space(char *line, int *i)
{
    while(line[*i] == ' ' || line[*i] == '\t')
    {
        (*i)++;
    }    
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        if (tokens->value)
            free(tokens->value);
        free(tokens);       
        tokens = tmp;
    }
}

int redir_out(char *line, int i, t_token *tokens)
{
    if(line[i + 1] == '>')
    {
        tokens->type = T_RED_OUT_APEND;
        tokens->value = ">>";
        i++;
    }
    else 
    {
        tokens->type = T_RED_OUT;
        tokens->value = ">";
    }
    return(i);
}

int redir_in(char *line, int i, t_token *tokens)
{
    if(line[i + 1] == '<')
    {
        tokens->type = T_HERDOC;
        tokens->value = "<<";
        i++;
    }
    else
    {
        tokens->type = T_RED_IN;
        tokens->value = "<";
    }
    return(i);
}

char *handel_redir(char *line, int (*i), t_token *tokens)
{
    if(line[(*i)] == '>')
    {
        *i = redir_out(line, *i, tokens);
    }
    else if(line[(*i)] == '<')
    {
        *i = redir_in(line, *i, tokens);
    }
    return(NULL);
}

int select_d_cots(char *line, int i, t_token *tokens)
{
    char *str;
    int u;
    int len;
    
    len = 0;
    u = i;
    while(line[u + 1] && line[++u] != '"')
        len++;
    str = malloc(sizeof(char) * (len + 3));
    if(!str)
        return(1);
    u = 0;
    str[u] = '"';
    while(++u <= len && line[++i])//to copie " 
    {
        str[u] = line[i];
    }
    str[u] = '"';
    str[++u] = '\0';
    tokens->value = str;
    return(i + 1);
}

int check_d(char *line, int i)
{
    while(line[++i])
    {
        if(line[i] == '"')
            return(1);
    }
    return(0);
}

char *handel_d_cots(char *line,int *i, t_token *tokens)
{
    char *str;
    int u;
    int len;

    len = 0;
    u = *i;
    tokens->type = T_D_COTS;
    if(check_d(line, *i) == 1)
    {
        tokens->type = T_COMMD;
        *i = select_d_cots(line, *i, tokens);
        return(NULL);
    }
    str = malloc(sizeof(char) * 2);
    if(!str)
        return(NULL);
    str[0] = '"';
    str[1] = '\0';
    tokens->value = str;
    return(NULL);
}


int select_s_cots(char *line, int i, t_token *tokens)
{
    char *str;
    int u;
    int len;
    
    len = 0;
    u = i;
    while(line[u + 1] && line[++u] != '\'')
        len++;
    str = malloc(sizeof(char) * (len + 3));
    if(!str)
        return(1);
    u = 0;
    str[u] = '\'';
    while(++u <= len && line[++i])//to copie " 
    {
        str[u] = line[i];
    }
    str[u] = '\'';
    str[++u] = '\0';
    tokens->value = str;
    return(i + 1);
}

int check_s(char *line, int i)
{
    while(line[++i])
    {
        if(line[i] == '\'')
            return(1);
    }
    return(0);
}

char *handel_s_cots(char *line,int *i, t_token *tokens)
{
    char *str;
    int u;
    int len;

    len = 0;
    u = *i;
    tokens->type = T_S_COTS;
    if(check_s(line, *i) == 1)
    {
        tokens->type = T_COMMD;
        *i = select_s_cots(line, *i, tokens);
        return(NULL);
    }
    str = malloc(sizeof(char) * 2);
    if(!str)
        return(NULL);
    str[0] = '\'';
    str[1] = '\0';
    tokens->value = str;
    return(NULL);
}

void handel_pipe(t_token *tokens)
{
    tokens->type = T_PIPE;
    tokens->value = "|";
}
