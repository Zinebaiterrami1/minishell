/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/15 10:22:44 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void cd_update_env(char *old_pwd, t_env **env)
// {
//     char *new_pwd;

//     new_pwd = getcwd(NULL, 0);
//     if(!new_pwd)
//         return ;
//     set_env_value(env,"OLDPWD", old_pwd);
//     set_env_value(env,"PWD", new_pwd);
//     free(new_pwd);
// }

// static int cd_change_directory(char *path, t_env **env)
// {
//     char *old_pwd;
 
//     old_pwd = getcwd(NULL, 0);
//     if(!old_pwd)
//         return (perror("cd"), 1);
//     if(chdir(path) != 0)
//     {
//         perror("cd");
//         free(old_pwd);
//         return (1);
//     }
//     cd_update_env(old_pwd, env);
//     free(old_pwd);
//     return (0);
// }

// int ft_cd(char **args, t_env **env)
// {
//     if (!args[1])
// 	{
// 		char *home = get_env_value(*env, "HOME");
// 		if (!home)
// 			return (printf("cd: HOME not set\n"), 1);
// 		return (cd_change_directory(home, env));
// 	}
// 	return (cd_change_directory(args[1], env));
// }

//cd

// int ft_cd(t_command *cmd, t_env **env)
// {
//     char *path;
//     char buffer[BUFFER_SIZE];
//     char *cwd;
//     //getting the cwd to take it as oldpwd, and when i do cd path i will do
//     //getcwd to take it as pwd
//     cwd = getcwd(buffer, BUFFER_SIZE);
//     // if(cmd->arg[4])
//     // {
//     //     printf("Error: too many arguments\n");
//     //     return (1);
//     // }
//     if(!cmd->arg[1])
//     {   
//         set_env_value(env, "OLDPWD", cwd);
//         path = get_env_value(*env, "HOME");
//         chdir(path); //go to home
//     }
//     if(cmd->arg[1])
//     {
//         set_env_value(env, "OLDPWD", cwd);
//         path = get_env_value(*env, cmd->arg[2]);
//         chdir(path); //if one arg passed to cd, i will take it as key and go to its value(path)
//     }
//     if(chdir(cmd->arg[1]) != 0)
//         printf("cd: no such file or directory: %s\n", cmd->arg[1]);
//     set_env_value(env, "PWD", path);
//     return (0);
// }

int verify_permission(t_command *cmd)
{
    //check if file exists first
    if(access(cmd->arg[1], F_OK) == -1)
    {
        g_exit_status = 127; //"command not found"
        return (0);
    }
    
    //check execute permission
    if(access(cmd->arg[1], X_OK) == -1)
    {
        g_exit_status = 126;
        return (0);
    }

    g_exit_status = 0;
    return (1);
}

//new cd
int ft_cd(t_command *cmd, t_env **env)
{
    char *old_path;
    char *new_path;

    if(!cmd->arg[1])
    {
        printf("must be a relative or absolute path\n");
        return (-1);
    }
    old_path = getcwd(NULL, 0);
    if(chdir(cmd->arg[1]) != 0)
    {
        perror("cd");
        //if file exists i will exit with 126 else 127
        verify_permission(cmd);
    }
    new_path = getcwd(NULL, 0);
    set_env_value(env, "PWD", new_path);
    set_env_value(env, "OLDPWD", old_path);
    // free(old_path);
    // free(new_path);
    return (0);
}

