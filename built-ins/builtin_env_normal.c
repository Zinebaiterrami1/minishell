#include "../includes/mini.h"
#include "../includes/minishell.h"


//char *init_env(char **envp); // to split "KEY=VALUE" into key and value
t_env *init_env(char **envp)
{
    char *copy_env;
    t_env *tmp = NULL;

    int i = 0;
    while(envp[i])
        i++;
    copy_env = malloc(sizeof(char) * (i + 1));
    i = 0;
    tmp = malloc(sizeof(t_cmd));
    if (!tmp)
    {
        free(copy_env);
        return (NULL);
    }
    while(envp[i])
    {
        copy_env[i] = ft_strdup(envp[i]); //copy each string
        i++;
    }
    copy_env[i] = 0;
    tmp->line = copy_env;
    return (tmp);
}

char* get_env(char **env,char *key)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(key);

    while(env[i])
    {
        if(ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
        {
            return (env[i] + len + 1);
        }
        i++;
    }
    return (NULL);
}

/*
env[i] = "HOME=/Users/zineb"
key = "HOME"
len = 4

Check:
- Does it match "HOME" for the first 4 characters?
- Is the next char '='?

If yes → return pointer to env[i] + 5 → `"/Users/zineb"`
*/

// void update_env(char *key, char *new_value, char **env)
// {
//     int i = 0;

//     int len = ft_strlen(key);
//     while(env[i])
//     {
//         if(ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
//         {
//             free(env[i]);
            
//             int total_len = ft_strlen(key) + 1 + ft_strlen(new_value) + 1;
//             env[i] = malloc(total_len);
//             ft_strlcpy(env[i], key, total_len);
//             ft_strlcat(env[i], "=", total_len);
//             ft_strlcat(env[i], new_value, total_len);
//             return ;
//         }
//         i++;
//     }
//     return ;
// }

/*
2. Implement helper functions:
You’ll need:

char *get_env_value(t_env *env, char *key);
→ to fetch $HOME, $PWD, $OLDPWD, etc.

void update_env(t_env *env, char *key, char *new_value);
→ to update variables like PWD, OLDPWD.

*/