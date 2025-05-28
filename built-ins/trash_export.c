/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:29 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/28 20:56:38 by zait-err         ###   ########.fr       */
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
//         ft_display_env(tmp);
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
/*sort----export*/
static void swap_nodes(t_env *export, t_env *export_next)
{
    char *tmp_key;
    char *tmp_value;
    char *tmp_line;
    
    tmp_key = export->env_key;
    tmp_value = export->env_value;
    tmp_line = export->line;
    
    export->env_key = export_next->env_key;
    export->env_value = export_next->env_value;
    export->line = export_next->line;
    
    export_next->env_key = tmp_key;
    export_next->env_value = tmp_value;
    export_next->line = tmp_line;
}

static t_env *sort_lst(t_env **export)
{
    t_env *tmp;
    
    tmp = *export;
    if(!export || !*export)
        return (NULL);
    while (tmp && tmp->next)
    {
        if(ft_strcmp(tmp->env_key, tmp->next->env_key) > 0)
            swap_nodes(tmp, tmp->next);
        tmp = tmp->next;
    }
    tmp = *export;
    return (tmp);
}

// int ft_export(t_command **cmd, t_env **env)
// {
//     t_env *tmp;
//     t_command *tmp1;
//     int i;
//     int j;
    
//     i = 1;
//     j = 0;
//     tmp = *env;
//     tmp1 = *cmd;
//     //case if no args provided
//     if(!(*cmd)->arg[i])
//     {
//         sort_lst(env);
//         while(tmp)
//         {
//             printf("declare -x %s\n", tmp->line);
//             tmp = tmp->next;
//         }
//         return (0);
//     }
//     //case if args is present
//     //we will start if i put one or more args with export
//     if((*cmd)->arg[i])
//     {
//         while(tmp1->arg[i])
//         {
//             while(tmp1->arg[i][j])
//             {
//                 if(!isalpha(tmp1->arg[i][j]) && tmp1->arg[i][j] != '_') // =
//                 {
//                     printf("export: '%s': not a valid identifier\n", tmp1->arg[i]);
//                     return(-1);
//                 }
//                j++; 
//             }
//             //hna ghangolih ila l9a chi charachers mn ghir _ ola letters
//             //i3tabro invalid identifier
//             i++;
//         }
//     }
//     //export arg1 ..... arg2 ..... argn
//     i = 1;
//     j = 0;
//     while(tmp1->arg[i])
//     {
//         if(ft_strchr(tmp1->arg[i], '='))
//         {
//             //It's something like VAR=value
//             split_and_set(tmp1->arg[i], env); //kifach nchd dak arg n splitih
//         }
//         else
//         {
//             //It's just VAR — declare it if not already in env
//             /*
//             check if the key is already exits:
//             --->if yes, do nothing
//             --->if no, add the key with an empty string as its value
//             */ //kifach n compari dak arg b env_key kamlin bach nchofo wash deja exists
//             if (!get_env_value(*env, tmp1->arg[i]))
//                 set_env_value(env, tmp1->arg[i], "");
//         }
//         i++;
//     }
//     return (0);
// }
// //ila knt dkhlt key already exits, and 9damo value khasni n asayniha lih tani 

/*hada logic tani bach khdmt mhm*/

// int is_valid_identifier(t_command *args)
// {
//     t_command *tmp;
//     int i;
//     int j;
    
//     i = 1;
//     j = 0;
//     tmp = args;
//     while(tmp->arg[i])
//     {
//         if(ft_isdigit(tmp->arg[1][0]))
//             break;
//         while(tmp->arg[i][j])
//         {
//             while(ft_isalpha(tmp->arg[i][j]) || ft_isdigit(tmp->arg[i][j]) || tmp->arg[i][j] == '_')
//             {
//                 if(!ft_isalpha(tmp->arg[i][j]) && !ft_isdigit(tmp->arg[i][j]) && tmp->arg[i][j] != '_')
//                     break;
//                 j++;
//             }    
//             i++;     
//         }
//     }
//     if(tmp->arg[i][j] == '\0' || tmp->arg[i][j] == '=')
//         return (0);
//     printf("invalid identifier %s\n", tmp->arg[i]);
//     return (-1);
// }

// int ft_export(t_command **cmd, t_env **export)
// {
//     t_env *tmp;
//     t_command *tmp1;
//     int i;
//     // int j;
    
//     i = 1;
//     // j = 0;
//     tmp = *export;
//     tmp1 = *cmd;
//     //case if no args provided
//     if(!(*cmd)->arg[i])
//     {
//         sort_lst(export);
//         while(tmp)
//         {
//             printf("declare -x %s\n", tmp->line);
//             tmp = tmp->next;
//         }
//     }
//     else
//     {
//         if((*cmd)->arg[i])
//         {
//             if(is_valid_identifier(tmp1) == -1) //validate the args
//                 return (-1);
//             //first case ghaloopi 3la tmp-arg ila kan key mhto f list w n3ti value diyalo null
//             //else nchdo kima howa w nhto as a line w nzido f node mn b3d nsipliti dakchi w nzido f list
//             while(tmp1->arg[i])
//             {
//                 if(ft_strchr(tmp1->arg[i], '='))
//                 {
//                     split_and_set(tmp1->arg[i], &tmp);
//                 }
//                 else
//                 {
//                     set_env_value(&tmp, tmp1->arg[i], "");
//                 }
//                 i++;
//             }
//         }
//     }
//     return (0);
// }


//first khasni n handli if the user dkha; gha export
//second nchof f case ilaa dkhloo bzzf diyal args
//so case 1
    //ila dkhl gha key kanchdo w nzido f back of the list 
    //with Null in the value,
    //else ila kaaan string arg fih '='
    //donc ghanzid dakchi li9bal as key dakchi limoraha as value
    //aslo ila 3awd dkhlt chi value w asaynit liha value n apdatiha f lis
    
