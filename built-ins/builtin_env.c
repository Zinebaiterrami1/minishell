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
    t_env *tmp2;
    cmd = init_env(envp);
    tmp = cmd;
    tmp2 = cmd;

    t_env *sp_env;
    t_env *tmp1;

    sp_env = split_env(tmp);
    tmp1 = sp_env;

    char *path;
    path = get_env_value(tmp, "PWD");
    

    char *key;
    key = get_env_key(tmp2, "unix:///run/user/102723/docker.sock");
    if(!tmp)
    {
        printf("Failed to initialize environment\n");
        return ;
    }
    /*---get the value of a key giving in params---*/
    // printf("PATH: %s\n", path);
    // printf("KEY: %s\n", key);
    /*---init env---*/
    while(tmp)
    {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    printf("-------------------------------------------\n");
    t_env *my_env = init_env(envp);
    my_env = split_env(my_env);
    t_env *current = my_env;
    printf("Before update:\n");
    while(my_env)
    {
        printf("key : %s ------- path : %s\n", my_env->env_key, my_env->env_value);
        my_env = my_env->next;
    }
    printf("after update:\n");
    set_env_value(&current, "USER", "zait-err");
    set_env_value(&current, "NEW_VAR", "hello_world");
    printf("current result:\n");
    while(current)
    {
        printf("key : %s ------- path : %s\n", current->env_key, current->env_value);
        current = current->next;
    }
    /*---split the env variables key=value---*/
    // while(tmp1)
    // {
    //     printf("key : %s ------- path : %s\n", tmp1->env_key, tmp1->env_value);
    //     tmp1 = tmp1->next;
    // }
}

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

char *get_env_key(t_env *env_lst, const char *value)
{
    t_env *tmp;
    char *key;
    
    tmp = env_lst;
    while(tmp)
    {
        if(ft_strncmp(tmp->env_value, value, ft_strlen(tmp->env_value)) == 0)
        {
            key = tmp->env_key;
        }
        tmp = tmp->next;
    }
    return (key);
}
// /* Update existing or add new environment variable */
void set_env_value(t_env **env_list, const char *key, const char *value)
{
    t_env *tmp;
    t_env *new_node;
    tmp = *env_list;
    if(!*env_list || !env_list || !tmp)
        return;
    while(tmp)
    {   
        if(ft_strncmp(tmp->env_key, key, ft_strlen(tmp->env_key)) == 0)
        {
            free(tmp->env_value);
            tmp->env_value = ft_strdup(value);
            return ;
        }
        if(tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
    new_node = malloc(sizeof(t_env));
    new_node->env_key = ft_strdup(key);
    new_node->env_value = ft_strdup(value);
    new_node->next = NULL;
    tmp->next = new_node;
    // ft_lstadd_back(tmp, new_node);
}