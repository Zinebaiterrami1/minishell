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

    if(!tmp)
    {
        printf("Failed to initialize environment\n");
        return ;
    }
    
    while(tmp)
    {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
}

// /* Get the value of a specific environment variable */
// char *get_env_value(t_env *env_list, const char *key);

// /* Update existing or add new environment variable */
// int set_env_value(t_env **env_list, const char *key, const char *value);