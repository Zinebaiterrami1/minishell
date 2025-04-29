#include "../includes/minishell.h"
#include "../includes/mini.h"

void ft_cd(t_cmd *arg, char *path)
{
    t_cmd *tmp;

    tmp = arg;
    if(ft_strncmp("cd", arg->value, ft_strlen("cd")) == 0)
    {
        if(tmp->next == NULL)
        {
            chdir(path);
            getenv(path);
        }
    }
}

//void    cd_cmd(char *path, t_env **env)