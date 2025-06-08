#include "includes/minishell.h"

int g_exit_status = 0;

// int g_last_status = 0;
// int main(int ac, char **argv, char **env)
// {
//     (void)ac;
//     (void)argv;
    
//     // t_token cmd = {argv[1], T_COMMD, NULL};
//     // t_token option = {argv[2], T_COMMD, NULL};
//     // t_token arg1 = {argv[3], T_ARG, NULL};
//     // t_token arg2 = {argv[4], T_ARG, NULL};
//     // cmd.next = &option;
//     // option.next = &arg1;
//     // arg1.next = &arg2;
//     // // cmd.next = &arg1;
//     // // arg1.next = &arg2;
// 	// ft_echo(&cmd);
//     // ft_pwd();
//     // char **envp = init_env(env);
//     // // int i = 0;

//     // // while(envp[i])
//     // //     printf("%s\n", envp[i++]);
//     // char *path = get_env(envp, "HOME");
//     // if (path)
//     // {
//     //     // Print the entire value of the "PATH" environment variable
//     //     printf("PATH: %s\n", path);  // Print the full string (value of PATH)
//     // }
//     // else
//     // {
//     //     printf("PATH not found\n");
//     // }
//     print_env(env, argv, ac);
// }

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

int is_buitins(t_command *list)
{
    return(!ft_strcmp(list->arg[0], "cd") || !ft_strcmp(list->arg[0], "echo") || !ft_strcmp(list->arg[0], "env")
            || !ft_strcmp(list->arg[0], "exit") || !ft_strcmp(list->arg[0], "export") || !ft_strcmp(list->arg[0], "pwd") || !ft_strcmp(list->arg[0], "unset"));
}

void execute_buitlins(t_env *m_env, t_command *cmd)
{
    // int (stdin), (stdout);

    // stdin = dup(STDIN_FILENO);
    // stdout = dup(STDOUT_FILENO);
    if(!m_env->env_key || !m_env->env_value || !cmd)
        return;
    if(ft_strcmp(cmd->arg[0], "echo") == 0)//no exec
        ft_echo(cmd);
    else if(ft_strcmp(cmd->arg[0], "cd") == 0)//SEGV
        ft_cd(cmd, &m_env);
    else if(ft_strcmp(cmd->arg[0], "env") == 0)//khdama
        ft_display_env(m_env);
    else if(ft_strcmp(cmd->arg[0], "pwd") == 0) //khdama
        ft_pwd();
    else if(ft_strcmp(cmd->arg[0], "export") == 0)//SEGV
        ft_export(&m_env, &cmd);
    else if(ft_strcmp(cmd->arg[0], "exit") == 0)//SEGV
        ft_exit(cmd);
    else if(ft_strcmp(cmd->arg[0], "unset") == 0)//SEGV
        ft_unset(&cmd, &m_env);
    // dup2(stdin, STDIN_FILENO);
    // dup2(stdout, STDOUT_FILENO);
    // close(stdin);
    // close(stdout);
}   

void signal_handler(int signal_num)
{
    if(signal_num == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env *env_lst;
    (void)argc;
    (void)argv;
    env_lst = init_env(envp);
    env_lst = split_env(env_lst);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, signal_handler);
    while(1)
    {
        line = readline("\001\033[1;36m\002$ \001\033[1;34m\002minishell V3 \001\033[0m\002 ");
        printf("%s\n", line);
        if(line == NULL)
        {
            free_all(getter());
            printf("exit with ctrl+d\n");//for ctrl+d, detect EOF
            break;
        }
        if (line[0] == '\0')
            continue;
        add_history(line);   
        if(!minishell(line, envp))
        {
            free(line);
            line = NULL;
            continue;
        }
        free(line);
        free_all(getter());
    }
}
