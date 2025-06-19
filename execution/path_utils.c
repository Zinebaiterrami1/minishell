/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:13:35 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/19 23:42:17 by zait-err         ###   ########.fr       */
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

void	signal_handler_child(int signal_num)
{
	if (signal_num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("Quit (core dumped)\n");
	}
}

void	execute_externals(t_command *cmd, t_env *env)
{
	int		f;
	char	*pathcmd;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if ((!cmd || !cmd->arg || !cmd->arg[0]) && cmd->redir)
		{
			open_file(cmd);
			return ;
		}
		f = open_file(cmd);
		if (f == -1)
			return ;
		handle_cases(cmd, env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

void	wait_child(pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		g_exit_status = 128 + sig;
	}
	else
		g_exit_status = WEXITSTATUS(status);
}
