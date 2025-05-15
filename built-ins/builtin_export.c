#include "../includes/minishell.h"
#include "../includes/mini.h"

int ft_export(char **args, t_env **env, char **envp)
{
    t_env *tmp;
    int i;
    int j;

    i = 1;
    j = 0;
    tmp = *env;
    if(!args[1])
    {
        ft_display_env(tmp, envp);
    }
    tmp = *env;
    if(args[1])
    {
        while(args[i][j])
        {
            if(args[i][0] != isalpha(args[i][0]) || args[i][0] != '_')
                printf("export: not an identifier: %s\n", args[i]);
            j++;
            if(args[i][j] == '=')
            {
                split_env(tmp);
                set_env_value(tmp, tmp->env_key, tmp->env_value);
            }
            else
            {
                set_env_value(tmp, tmp->env_key, NULL);
            }
            i++;
            j++;
        }
    }
}
