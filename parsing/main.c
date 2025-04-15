/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:28:05 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/15 12:54:46 by nel-khad         ###   ########.fr       */
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
    char *l;
    
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
    tokens->num_d_cots++;
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
    tokens->num_d_cots = 0;
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
    tokens->num_d_cots++;
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
    tokens->num_s_cots++;
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
    tokens->num_s_cots = 0;
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
    tokens->num_s_cots++;
    return(NULL);
}

void handel_pipe(t_token *tokens)
{
    tokens->type = T_PIPE;
    tokens->value = "|";
    tokens->next = NULL;
}

void handel_else(char *line, t_token *tokens)
{
    tokens->type = T_COMMD;
    tokens->value = line;
}
t_token *lexer(char *line)
{
    int i;
    t_token_type type;
    t_token *tokens;

    tokens = NULL;
    i = 0;
    while(line[i])
    {
        skip_space(line, &i);
        tokens = malloc(sizeof(t_token));
        if(line[i] == '|')
        {
            handel_pipe(tokens);
        }
        else if(line[i] == '>' || line[i] == '<')
            handel_redir(line, &i, tokens);
        else if(line[i] == '"')
            handel_d_cots(line, &i, tokens);
        else if(line[i] == '\'')
            handel_s_cots(line, &i, tokens);
        else
            handel_else(&line[i], tokens);
        printf("-------------> %s\n", tokens->value);
        printf("i ======= %d\n", i);
        //free(tokens -> value / tokens)
        i++;
    }
    return(NULL);
}

int main()
{
    char *line;
    while(1)
    {
        line = readline("minishell$ ");
        if(!line)
            break;
        add_history(line);
        lexer(line);
        free(line);
    }
}