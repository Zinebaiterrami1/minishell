#include "includes/minishell.h"
#include "includes/mini.h"

int main(int ac, char **argv, char **env)
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
    // ft_pwd();
    // char **envp = init_env(env);
    // // int i = 0;

    // // while(envp[i])
    // //     printf("%s\n", envp[i++]);
    // char *path = get_env(envp, "HOME");
    // if (path)
    // {
    //     // Print the entire value of the "PATH" environment variable
    //     printf("PATH: %s\n", path);  // Print the full string (value of PATH)
    // }
    // else
    // {
    //     printf("PATH not found\n");
    // }

    print_env(env);

}

// int main(int argc, char **argv)
// {
//     (void)argv;
//     (void)argc;
//     // Assume init_env() sets up a list like:
//     // HOME=/home/user
//     // PATH=/usr/bin:/bin

//     char *envp[] = {
//         "HOME=/home/user",
//         "PATH=/usr/bin:/bin",
//         "USER=guest",
//         NULL
//     };
    
//     // Initialize env from envp array
//     char **env = init_env(envp);

//     // Test update_env function
//     printf("Before update:\n");
//     for (int i = 0; env[i]; i++)
//         printf("%s\n", env[i]);

//     // Update "HOME" variable
//     update_env("HOME", "/home/zineb", env);

//     // Update "PATH" variable
//     update_env("PATH", "/usr/local/bin:/usr/bin:/bin", env);

//     // Print after updates
//     printf("\nAfter update:\n");
//     for (int i = 0; env[i]; i++)
//         printf("%s\n", env[i]);

//     // Free memory (in your actual code, make sure to free memory where needed)
//     // for (int i = 0; env[i]; i++)
//     //     free(env[i]);
//     // free(env);

//     return 0;
// }

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
