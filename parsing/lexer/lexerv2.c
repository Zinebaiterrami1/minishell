/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:59 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/22 15:23:47 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mimi.h"


int lexer(char *line)
{
    
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
        lexer(line);
        if(lexer(line) == 1)
        {
            free(line);
            continue;
        }
        free(line);
    }
    
}