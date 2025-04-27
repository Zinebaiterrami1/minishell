#include "../includes/mini.h"
#include "../includes/minishell.h"

/* Initialize environment variables from system env */
t_env *init_env(char **envp)
{
    int i;
    t_env *head;
    t_env *tmp;

    head = NULL;
    tmp = NULL;
    i = 0;
    while(envp[i])
    {
        t_env *new_node = malloc(sizeof(t_env));
        new_node->line = envp[i];
        new_node->env_key = NULL;
        new_node->env_value = NULL;
        new_node->next = NULL;
        if(!head)
            head = new_node;
        else
            tmp->next = new_node;
        tmp = new_node;
        i++;
    }
    return (head);
}

// /* Print all environment variables (env builtin) */
void print_env(char **envp)
{
    t_env *cmd;
    t_env *tmp;
    cmd = init_env(envp);
    tmp = cmd;

    t_env *sp_env;
    t_env *tmp1;

    sp_env = split_env(tmp);
    tmp1 = sp_env;

    char *path;
    path = get_env_value(tmp, "PWD");
    if(!tmp)
    {
        printf("Failed to initialize environment\n");
        return ;
    }
    printf("PATH: %s\n", path);
    // while(tmp)
    // {
    //     printf("%s\n", tmp->line);
    //     tmp = tmp->next;
    // }

    // while(tmp1)
    // {
    //     printf("key : %s ------- path : %s\n", tmp1->env_key, tmp1->env_value);
    //     tmp1 = tmp1->next;
    // }
}
//
// t_env *split_env(t_env *lst, char **envp)
// {
//     t_env *tmp;
//     char *key;

//    lst = init_env(envp);
//    tmp = lst;
//    while(tmp)
//    {    
//         key = ft_strchr(tmp->line, '=');
//         tmp->env_key = ft_strdup(key);
//         tmp = tmp->next;
//    }
//     return (lst);
// }

t_env *split_env(t_env *lst)
{
    t_env *tmp;
    char *equal_env;
    int key_len;

    tmp = lst;

    while(tmp)
    {
        equal_env = ft_strchr(tmp->line, '=');
        key_len = equal_env - tmp->line;
        tmp->env_key = ft_substr(tmp->line, 0, key_len);
        tmp->env_value = ft_strdup(equal_env + 1);
        tmp = tmp->next;
    }
    return (lst);
}

/* Get the value of a specific environment variable */
char *get_env_value(t_env *env_list, const char *key)
{
    t_env *tmp;
    char *path;

    tmp = env_list;
    while(tmp)
    {
        if(ft_strncmp(tmp->env_key, key, ft_strlen(key)) == 0)
        {
            path = tmp->env_value;
        }
        tmp = tmp->next;
    }
    return (path);
}

// /* Update existing or add new environment variable */
// int set_env_value(t_env **env_list, const char *key, const char *value);