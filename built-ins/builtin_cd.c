#include "../includes/minishell.h"
#include "../includes/mini.h"

static int  change_home(t_env *env)
{
    int is_foud;

    is_foud = 0;
    while(env)
    {
        if(ft_strncmp(env->env_key, "HOME", ft_strlen(env->env_key)) == 0)
        {
            if(chdir(env->env_value) == -1)
            {
                perror("cd");
                return (-1);
            }
            is_foud++;
            break;
        }
        env = env->next;
    }
    if(is_foud == 0)
    {
        printf("cd: HOME not set\n");
        return (-1);
    }
    return (0);
}


static void    update_pwd(t_env **env, char *path, char hint)
{
    t_env   *lst;

    lst = *env;
    while(lst)
    {
        if(hint == 'P' && (ft_strncmp(lst->env_key, "PWD", ft_strlen(lst->env_key)) == 0))
            {
                free(lst->env_value);
                lst->env_value = ft_strdup(path);
                break;
            }
        else if(hint == 'O' && (ft_strncmp(lst->env_key, "OLDPWD", ft_strlen(lst->env_key)) == 0))
            {
                free(lst->env_value);
                lst->env_value = ft_strdup(path);
                break;
            }
        lst = lst->next;
    }
}

static int    update_pwd2(t_env **env, char **old)
{
        update_pwd(env, *old, 'O');
            free(*old);
        *old = getcwd(NULL, 0);
        update_pwd(env, *old, 'P');
        free(*old);
        return (0);
}

int    ft_cd(char **args, t_env **env)
{
    char    *old;

    old = getcwd(NULL, 0);
    if((!args || !args[0]) || (ft_strncmp(args[0], "~", ft_strlen(args[0])) == 0 && !args[1]))
    {
        if(change_home(*env) == -1)
        {
                free(old);
                return (-1);
        }
    }
    else if(args[1])
    {
        printf("cd: too many arguments\n");
        free(old);
        return (-1);
    }
    else if(chdir(*args) == -1)
    {
        perror("cd");
        free(old);
        return (-1);
    }
    if(update_pwd2(env, &old) == -1) return (-1); 
    return (0);
}