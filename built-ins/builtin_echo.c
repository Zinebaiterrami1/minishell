#include "../includes/minishell.h"
#include "../includes/mini.h"

void ft_echo(t_token *cmd)
{
    if(ft_strncmp("echo", cmd->value, ft_strlen("echo")) == 0)
    {
        t_token *tmp;
        tmp = cmd->next;
        if(tmp && ft_strncmp("-n", tmp->value, ft_strlen("-n")) == 0)
        {
            tmp = tmp->next;
            while(tmp)
            {
                write(1, tmp->value, ft_strlen(tmp->value));
                if(tmp->next != NULL)
                    write(1, " ", 1);
                tmp = tmp->next;
            }
        }
        else 
        {
            while(tmp)
            {
                write(1, tmp->value, ft_strlen(tmp->value));
                if(tmp->next != NULL)
                    write(1, " ", 1);
                tmp = tmp->next;
            }
            write(1, "\n", 1);
        }
    }
}

// void ft_echo_in_file(int fd)
// {

// }
/*
1. write(1, &cmd->args[i], 1); is wrong
cmd->args[i] is a char * (a string).

&cmd->args[i] is a pointer to that string → char **

write() expects a pointer to characters (char *), not a pointer to a pointer.

✅ Fix: Use write(1, cmd->args[i], ft_strlen(cmd->args[i])) to print the whole string.
*/