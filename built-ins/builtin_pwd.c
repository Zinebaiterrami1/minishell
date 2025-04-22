#include "../includes/minishell.h"
#include "../includes/mini.h"

void ft_pwd()
{
    char buffer[BUFFER_SIZE];
    if(getcwd(buffer, BUFFER_SIZE) == NULL)
        write(2, "Cannot get the current directory ... !\n", ft_strlen("Cannot get the current directory ... !\n"));
    else
        write(1, buffer, ft_strlen(buffer));
    write(1, "\n", 1);
}