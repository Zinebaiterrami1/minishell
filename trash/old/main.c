// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/11 18:28:05 by nel-khad          #+#    #+#             */
// /*   Updated: 2025/06/03 21:27:16 by zait-err         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "mimi.h"

// // void skip_space(char *line, int *i)
// // {
// //     while(line[*i] == ' ' || line[*i] == '\t')
// //     {
// //         (*i)++;
// //     }    
// // }

// // int redir_out(char *line, int i, t_token *tokens)
// // {
// //     if(line[i + 1] == '>')
// //     {
// //         tokens->type = T_RED_OUT_APEND;
// //         tokens->value = ">>";
// //         i++;
// //     }
// //     else 
// //     {
// //         tokens->type = T_RED_OUT;
// //         tokens->value = ">";
// //     }
// //     return(i);
// // }

// // int redir_in(char *line, int i, t_token *tokens)
// // {
// //     if(line[i + 1] == '<')
// //     {
// //         tokens->type = T_HERDOC;
// //         tokens->value = "<<";
// //         i++;
// //     }
// //     else
// //     {
// //         tokens->type = T_RED_IN;
// //         tokens->value = "<";
// //     }
// //     return(i);
// // }

// // char *handel_redir(char *line, int (*i), t_token *tokens)
// // {
// //     if(line[(*i)] == '>')
// //     {
// //         *i = redir_out(line, *i, tokens);
// //     }
// //     else if(line[(*i)] == '<')
// //     {
// //         *i = redir_in(line, *i, tokens);
// //     }
// //     return(NULL);
// // }

// // int select_d_cots(char *line, int i, t_token *tokens)
// // {
// //     char *str;
// //     int u;
// //     int len;
    
// //     len = 0;
// //     u = i;
// //     while(line[u + 1] && line[++u] != '"')
// //         len++;
// //     str = malloc(sizeof(char) * (len + 3));
// //     if(!str)
// //         return(1);
// //     u = 0;
// //     str[u] = '"';
// //     while(++u <= len && line[++i])//to copie " 
// //     {
// //         str[u] = line[i];
// //     }
// //     str[u] = '"';
// //     str[++u] = '\0';
// //     tokens->value = str;
// //     tokens->num_d_cots++;
// //     return(i + 1);
// // }

// // int check_d(char *line, int i)
// // {
// //     while(line[++i])
// //     {
// //         if(line[i] == '"')
// //             return(1);
// //     }
// //     return(0);
// // }

// // char *handel_d_cots(char *line,int *i, t_token *tokens)
// // {
// //     char *str;
// //     int u;
// //     int len;

// //     len = 0;
// //     u = *i;
// //     tokens->num_d_cots = 0;
// //     tokens->type = T_D_COTS;
// //     if(check_d(line, *i) == 1)
// //     {
// //         tokens->type = T_COMMD;
// //         *i = select_d_cots(line, *i, tokens);
// //         return(NULL);
// //     }
// //     str = malloc(sizeof(char) * 2);
// //     if(!str)
// //         return(NULL);
// //     str[0] = '"';
// //     str[1] = '\0';
// //     tokens->value = str;
// //     tokens->num_d_cots++;
// //     return(NULL);
// // }


// // int select_s_cots(char *line, int i, t_token *tokens)
// // {
// //     char *str;
// //     int u;
// //     int len;
    
// //     len = 0;
// //     u = i;
// //     while(line[u + 1] && line[++u] != '\'')
// //         len++;
// //     str = malloc(sizeof(char) * (len + 3));
// //     if(!str)
// //         return(1);
// //     u = 0;
// //     str[u] = '\'';
// //     while(++u <= len && line[++i])//to copie " 
// //     {
// //         str[u] = line[i];
// //     }
// //     str[u] = '\'';
// //     str[++u] = '\0';
// //     tokens->value = str;
// //     tokens->num_s_cots++;
// //     return(i + 1);
// // }

// // int check_s(char *line, int i)
// // {
// //     while(line[++i])
// //     {
// //         if(line[i] == '\'')
// //             return(1);
// //     }
// //     return(0);
// // }

// // char *handel_s_cots(char *line,int *i, t_token *tokens)
// // {
// //     char *str;
// //     int u;
// //     int len;

// //     len = 0;
// //     u = *i;
// //     tokens->num_s_cots = 0;
// //     tokens->type = T_S_COTS;
// //     if(check_s(line, *i) == 1)
// //     {
// //         tokens->type = T_COMMD;
// //         *i = select_s_cots(line, *i, tokens);
// //         return(NULL);
// //     }
// //     str = malloc(sizeof(char) * 2);
// //     if(!str)
// //         return(NULL);
// //     str[0] = '\'';
// //     str[1] = '\0';
// //     tokens->value = str;
// //     tokens->num_s_cots++;
// //     return(NULL);
// // }


// // void handel_else(char *line, int *i, t_token *tokens)
// // {
// //     char *str;
// //     int u;
// //     int len;

// //     u = *i;
// //     len = 0;
// //     tokens->type = T_COMMD;
// //     while(line[u] && line[u] != ' ' && line[u] != '\t')
// //     {
// //         len++;
// //         u++;
// //     }
// //     u = 0;
// //     str = malloc(sizeof(char) * (len + 1));
// //     if(!str)
// //         return;
// //     while(line[*i] && u < len)
// //     {
// //         str[u++] = line[(*i)++];
// //     }
// //     str[u] = '\0';
// //     tokens->value = str;
// // }


// // int help(t_check *check, char **line)
// // {
// //     char quote_char;
// //     int error;
    
// //     error = 0;
// //     // check->quote_open = 0;

// //     quote_char = **line;
// //     check->quote_open = 1;
// //     (*line)++;
// //     while(**line && **line != quote_char)
// //         (*line)++;
// //     if (**line == quote_char)
// //     {
// //         check->quote_open = 0;
// //         (*line)++;
// //     }
// //     else
// //         error = 1;
// //     return(error);
// // }

// // int check_if_closed(char *line, t_token *tokens, t_token *new)
// // {
// //     t_check check;
    
// //     int error;

// //     error = 0;
// //     check.parth_d = 0;
// //     check.parth_g = 0;
// //     check.quote_open = 0;
// //     while(*line)
// //     {
// //         if(*line == '\'' || *line == '"')
// //             error = help(&check, &line);
// //         if(*line == '(' && !check.quote_open)
// //             check.parth_g++;
// //         if(*line == ')'&& !check.quote_open)
// //             check.parth_d++;
// //         if(*line)
// //             line++;
// //     }
// //     if(error || (check.parth_d - check.parth_g) != 0)
// //         error_exit("syntax error", 2, tokens, new);
// //     return(0);
// // }
// // int select_parenth(char *line, int i, t_token *tokens)
// // {
// //     int start = i;
// //     int end = -1;
// //     char quote;
// //     char *str;

// //     while (line[++i])
// //     {
// //         if (line[i] == '\'' || line[i] == '"')
// //         {
// //             quote = line[i++];
// //             while (line[i] && line[i] != quote)
// //                 i++;
// //             if (!line[i])
// //                 return (-1); // quote non fermée
// //         }
// //         if (line[i] == ')')
// //         {
// //             end = i;
// //             break;
// //         }
// //     }
// //     if (end == -1)
// //         return (-1); // pas de parenthèse fermante

// //     int len = end - start + 1; // longueur à copier
// //     str = malloc(len + 1);
// //     if (!str)
// //         return (1);

// //     for (int j = 0; j < len; j++)
// //         str[j] = line[start + j];
// //     str[len] = '\0';

// //     tokens->value = str;
// //     return (end + 1); // renvoie la nouvelle position dans line
// // }

// // int select_parenth(char *line, int i, t_token *tokens)
// // {
// //     char *str;
// //     int u;
// //     int len;
// //     char c;
    
// //     len = 0;
// //     u = i;
// //     while(line[++u])
// //     {
// //         if(line[u] == '"' || line[u] == '\'')
// //         {
// //             c = line[u];
// //             u++;
// //             while(line[u] && line[u] != c)
// //                 u++;
// //             if(line[u] != c)
// //                 return(-1);
// //         }
// //         if(line[u] == ')')
// //             len = u - i + 1;
// //     }
// //     str = malloc(sizeof(char) * (len + 3));
// //     if(!str)
// //         return(1);
// //     u = 0;
// //     str[u] = '(';
// //     while(++u < len && line[++i])
// //     {
// //         str[u] = line[i];
// //     }
// //     str[u] = ')';
// //     str[++u] = '\0';
// //     tokens->value = str;
// //     return(i + 1);
// // }

// int check_p(char *line, int i)
// {
//     char c;
//     while(line[++i])
//     {
//         if(line[i] == '"' || line[i] == '\'')
//         {
//             c = line[i];
//             i++;
//             while(line[i] != c)
//                 i++;
//         }
//         if(line[i] == ')')
//             return(1);
//     }
//     return(0);
// }

// int handel_parenth(char *line,int *i, t_token *tokens)
// {
//     char *str;
//     // int len;

//     // len = 0;
//     tokens->type = T_PAR;
//     if(check_p(line, *i) == 1)
//     {
//         tokens->type = T_COMMD;
//         *i = select_parenth(line, *i, tokens);
//         if (*i == -1)
//             return(1);
//         return(0);
//     }
//     str = malloc(sizeof(char) * 2);
//     if(!str)
//         return(0);
//     str[0] = line[*i];////////////////////////////////////////////////
//     str[1] = '\0';
//     tokens->value = str;
//     return(0);
// }

// void print_list(t_token *list)
// {
//     while(list)
//     {
//         printf("%s ==> ", list->value);
//         list = list->next;
//     }
//     printf("\n");
// }

// t_token *lexer(char *line)
// {
//     int i;
//     t_token *tokens;
//     t_token *new;
//     // int error;                                                                           should be returned by all functions 
//     // t_check check;

//     // check.quote_open = 0;
//     new = NULL;
//     tokens = NULL;
//     i = 0;
//     while(line[i])
//     {
//         check_if_closed(line, tokens, new);
//         skip_space(line, &i);
//         new = malloc(sizeof(t_token));
//         if(line[i] == '|')
//         {
//             handel_pipe(new);
//         }
//         else if(line[i] == '>' || line[i] == '<')
//             handel_redir(line, &i, new);
//         else if(line[i] == '"')
//             handel_d_cots(line, &i, new);
//         else if(line[i] == '\'')
//             handel_s_cots(line, &i, new);        
//         else if(line[i] == '(' || line[i] == ')')
//             handel_parenth(line, &i, new);
//         else if(line[i])
//             handel_else(line, &i, new);
//         new->next = NULL;
//         ft_lstadd_back(&tokens,new);
//         if(!line[i])
//             break;
//         i++;
//     }
//     print_list(tokens);
//     free_tokens(tokens);
//     return(NULL);
// }

// // int main()
// // {
// //     char *line;
// //     while(1)
// //     {
// //         line = readline("minishell$ ");
// //         if(!line)
// //             break;
// //         add_history(line);
// //         lexer(line);
// //         free(line);
// //     }
// // }
