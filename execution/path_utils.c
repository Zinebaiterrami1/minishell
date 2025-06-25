/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:13:35 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 16:22:20 by zait-err         ###   ########.fr       */
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
	t_pipes p;
	
	if ((!cmd || !cmd->arg || !cmd->arg[0]) && cmd->redir)
	{
		if(open_file(cmd) == -1)
		{
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
	wait_children(&p);
}
