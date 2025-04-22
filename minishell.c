#include "includes/minishell.h"
#include "includes/mini.h"

int main(int ac, char **argv)
{
    (void)ac;
    (void)argv;
    
    // t_token cmd = {argv[1], T_COMMD, NULL};
    // t_token option = {argv[2], T_COMMD, NULL};
    // t_token arg1 = {argv[3], T_ARG, NULL};
    // t_token arg2 = {argv[4], T_ARG, NULL};
    // cmd.next = &option;
    // option.next = &arg1;
    // arg1.next = &arg2;
    // // cmd.next = &arg1;
    // // arg1.next = &arg2;
	// ft_echo(&cmd);
    ft_pwd();
    
}


// int main()
// {
//     char *line;
//     while(1)
//     {
//         line = readline("minishell$ ");
//         if(!line)
//             break;
//         add_history(line);
//         t_token *cmd = (t_token *)line;
//         ft_echo(cmd);
//         free(line);
//     }
// }
