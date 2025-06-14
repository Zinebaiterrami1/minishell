/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:40 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/14 23:45:11 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//chno kadir katchd ay env var kat deletih hadchi li kadir
/*
unset zineb=allo
unset: zineb=allo: invalid parameter name

export zineb=allo
unset zineb .... valid
case with no args 
unset: not enough arguments

typedef struct s_command
{
    char **arg;
    t_redir *redir;
    struct s_command *next_com;
} t_command;

*/

// int ft_unset(t_command **cmd, t_env **env)
// {
//     t_command *tmp;
//     t_env *tmp1;
//     t_command *ptr;
//     int i;
    
//     i = 0;
//     ptr = *cmd;
//     tmp = *cmd;
//     tmp1 = *env;
//     if(!tmp->arg[1])
//         printf("unset: not enough arguments\n");
//     while(ptr->arg[1][i])
//     {
//         if(ptr->arg[1][i] == '=')
//         {
//             printf("unset: %s: invalid parameter name\n", ptr->arg[1]);
//             break;
//         }
//         i++;
//     }
//     while(tmp)
//     {
//         if(ft_strcmp(tmp->arg[1], tmp1->env_key) == 0)
//         {
//             free(tmp1->env_key);
//             free(tmp1->env_value);
//             return (0);
//         }
//         tmp = tmp->next_com;
//         tmp1 = tmp1->next;
//     }
//     return (-1);
// }


void ft_unset(t_command **cmd, t_env **env)
{
	t_env *current;
	t_env *previous;
    t_command *tmp;
    
    tmp = *cmd;
	int i = 1;

	if(!tmp->arg[1])
	{
		g_exit_status = 1;
        return ;
	}
	while (tmp->arg[i])
	{
		current = *env;
		previous = NULL;
		while (current)
		{
			if (ft_strcmp(current->env_key, tmp->arg[i]) == 0)
			{
				if (previous)
					previous->next = current->next;
				else
					*env = current->next;
				free(current->env_key);
				free(current->env_value);
				free(current);
				break;
			}
			previous = current;
			current = current->next;
		}
		i++;
	}
	g_exit_status = 0;
}
