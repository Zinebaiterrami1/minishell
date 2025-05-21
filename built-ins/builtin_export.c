/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:29 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/20 14:59:20 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/mini.h"

// int ft_export(char **args, t_env **env, char **envp)
// {
//     t_env *tmp;
//     int i;
//     int j;

//     i = 1;
//     j = 0;
//     tmp = *env;
//     if(!args[1])
//     {
//         ft_display_env(tmp, envp);
//     }
//     tmp = *env;
//     if(args[1])
//     {
//         while(args[i][j])
//         {
//             if(args[i][0] != isalpha(args[i][0]) || args[i][0] != '_')
//                 printf("export: not an identifier: %s\n", args[i]);
//             j++;
//             if(args[i][j] == '=')
//             {
//                 split_env(tmp);
//                 set_env_value(tmp, tmp->env_key, tmp->env_value);
//             }
//             else
//             {
//                 set_env_value(tmp, tmp->env_key, NULL);
//             }
//             i++;
//             j++;
//         }
//     }
// }

int ft_export(t_command **cmd, t_env **env)
{
    t_env *tmp;
    t_command *tmp1;
    int i;
    int j;
    
    i = 2;
    j = 0;
    tmp = *env;
    tmp1 = *cmd;
    //case if no args provided
    if(!(*cmd)->arg[i])
    {
        while(tmp)
        {
            printf("declare -x %s\n", tmp->line);
            tmp = tmp->next;
        }
        return (0);
    }
    //case if args is present
    //we will start if i put one or more args with export
    while(tmp1->arg[i])
    {
        while(tmp1->arg[i][j])
        {
            if(!isalpha(tmp1->arg[i][j]) && tmp1->arg[i][j] != '_') // =
            {
                printf("export: '%s': not a valid identifier\n", tmp1->arg[i]);
                return(-1);
            }
           j++; 
        }
        //hna ghangolih ila l9a chi charachers mn ghir _ ola letters
        //i3tabro invalid identifier
        i++;
    }
    //export arg1 ..... arg2 ..... argn
    i = 2;
    j = 0;
    while(tmp1->arg[i])
    {
        if(ft_strchr(tmp1->arg, '='))
        {
            //It's something like VAR=value
            split_and_set(tmp1->arg[i], env); //kifach nchd dak arg n splitih
        }
        else
        {
            //It's just VAR — declare it if not already in env
            /*
            check if the key is already exits:
            --->if yes, do nothing
            --->if no, add the key with an empty string as its value
            */ //kifach n compari dak arg b env_key kamlin bach nchofo wash deja exists
            if (!get_env_value(*env, tmp1->arg[i]))
                set_env_value(env, tmp1->arg[i], "");
        }
        i++;
    }
    return (0);
}

//ila knt dkhlt key already exits, and 9damo value khasni n asayniha lih tani 
