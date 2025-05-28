/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:07:52 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/28 15:46:34 by zait-err         ###   ########.fr       */
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

int ft_cd(t_command *cmd, t_env **env)
{
    char *path;
    char buffer[BUFFER_SIZE];
    char *cwd;
    //getting the cwd to take it as oldpwd, and when i do cd path i will do
    //getcwd to take it as pwd
    cwd = getcwd(buffer, BUFFER_SIZE);
    if(cmd->arg[4])
    {
        printf("Error: too many arguments\n");
        return (1);
    }
    if(!cmd->arg[2])
    {   
        set_env_value(env, "OLDPWD", cwd);
        path = get_env_value(*env, "HOME");
        chdir(path); //go to home
    }
    if(cmd->arg[2])
    {
        set_env_value(env, "OLDPWD", cwd);
        path = get_env_value(*env, cmd->arg[2]);
        chdir(path); //if one arg passed to cd, i will take it as key and go to its value(path)
    }
    if(chdir(cmd->arg[2]) != 0)
        printf("cd: no such file or directory: %s\n", cmd->arg[2]);
    set_env_value(env, "PWD", path);
    return (0);
}