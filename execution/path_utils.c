/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:13:35 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 02:16:33 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_envp(t_env *lst)
{
	int		i;
	char	**envp;
	int		size;

	size = ft_lstsize(lst);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (lst)
	{
		envp[i] = lst->line;
		i++;
		lst = lst->next;
	}
	envp[i] = NULL;
	return (envp);
}

// void	signal_handler_child(int signal_num)
// {
// 	if (signal_num == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else
// 	{
// 		printf("Quit (core dumped)\n");
// 	}
// }

// void	wait_child(pid_t pid)
// {
// 	int	status;
// 	int	sig;

// 	waitpid(pid, &status, 0);
// 	if (WIFSIGNALED(status))
// 	{
// 		sig = WTERMSIG(status);
// 		if (sig == SIGINT)
// 			write(1, "\n", 1);
// 		else if (sig == SIGQUIT)
// 			write(1, "Quit (core dumped)\n", 20);
// 		g_exit_status = 128 + sig;
// 	}
// }

void	execute_externals(t_command *cmd, t_env *env)
{
	// pid_t	pid;
	t_pipes p;
	
	// p = NULL;
	if ((!cmd || !cmd->arg || !cmd->arg[0]) && cmd->redir)
	{
		if(open_file(cmd) == -1)
		{
			printf("9\n");
			g_exit_status = 1;
			exit(g_exit_status);
		}
		else
		{
			open_file(cmd);
			g_exit_status = 1;
			return ;
		}
	}
	ignore_signals();
	p.nb_cmd = 1;
	p.pid = fork();
	if (p.pid == 0)
	{
		printf("pid in fct:%d\n", p.pid);
		setup_signals_child();
		if(open_file(cmd) == -1) // clean_and_exit(int exit_status)
			exit(g_exit_status = 1);
		// handle_cases(cmd, env);
		fprintf(stderr, "DEBUG: inside child, before handle_cases()\n");
		handle_cases(cmd, env);
		fprintf(stderr, "DEBUG: if you see this, execve failed unexpectedly\n");
		// perror("minishell");
		// exit(EXIT_FAILURE);
	}
	// wait_child(pid);
	wait_children(&p);
}



// void execute_externals(t_command *cmd, t_env *env)
// {
//     char **envp;
//     int f;
//     char *pathcmd;
//     pid_t pid;
//     // int status;
//     signal(SIGINT, SIG_IGN);
//     signal(SIGQUIT, SIG_IGN);
//     pid = fork();
//     if(pid == 0)
//     {
//         signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_DFL);
//         if ((!cmd || !cmd->arg || !cmd->arg[0]) && cmd->redir)
//         {
//             open_file(cmd);
//             return ; // or return NULL or handle properly
//         }
//         envp = get_envp(env);
//         f = open_file(cmd);
//         if(f == -1)
//             return;
//         pathcmd = search_cmd(cmd, env);
//         if(ft_strcmp(pathcmd, ".") == 0)
//         {
//             printf(".: filename argument required\n");
//             printf(".: usage: . filename [arguments]\n");
//             g_exit_status = 2;
//             exit(g_exit_status);
//         }
//         if(!pathcmd)
//         {
//             printf("minishell: %s command not found\n", cmd->arg[0]);
//             g_exit_status = 127;
//             exit(g_exit_status);
//         }    
//         execve(pathcmd, cmd->arg, envp); //get envp from linked list t_env*;
//         perror("minishell");
//         exit(EXIT_FAILURE);
//     }
//     int status;
//     waitpid(pid, &status, 0);
// 	printf("---status:%d\n", status);
// 	printf("---g exit status:%d\n", g_exit_status);
//     if (WIFSIGNALED(status))
//     {
//         int sig = WTERMSIG(status);
//         if (sig == SIGINT)
//             write(1, "\n", 1);
//         else if (sig == SIGQUIT)
//             write(1, "Quit (core dumped)\n", 20);
//         g_exit_status = 128 + sig;
//     }
//     else
// 	{
//         g_exit_status = WEXITSTATUS(status);
// 		printf("---status:%d\n", status);
// 		printf("---g exit status:%d\n", g_exit_status);
// 	}
		
//     // wait(NULL);
//     // int status;
//     // waitpid(pid, &status, 0);
//     // if (WIFSIGNALED(status))
//     //     g_exit_status = 128 + WTERMSIG(status); // like bash: 130 for SIGINT, 131 for SIGQUIT
//     // else
//     //     g_exit_status = WEXITSTATUS(status);
//     // waitpid(pid, &status, 0);
//     // exit(WEXITSTATUS(status));
// }