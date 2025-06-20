/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:03:05 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/20 20:57:59 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_exit_status = 0;

int	is_buitins(t_command *list)
{
	return (!ft_strcmp(list->arg[0], "cd") || !ft_strcmp(list->arg[0], "echo")
		|| !ft_strcmp(list->arg[0], "env") || !ft_strcmp(list->arg[0], "exit")
		|| !ft_strcmp(list->arg[0], "export") || !ft_strcmp(list->arg[0], "pwd")
		|| !ft_strcmp(list->arg[0], "unset"));
}

void	execute_buitlins(t_env **m_env, t_command *cmd)
{
	if (!(*m_env)->env_key || !(*m_env)->env_value || !cmd)
		return ;
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		ft_cd(cmd, m_env);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		ft_display_env(*m_env, cmd);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		ft_export(m_env, &cmd);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		ft_unset(&cmd, m_env);
}

void	signal_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

static void	setup_minishell(char *line, t_env *env_lst)
{
	while (1)
	{
		line = readline(PINK "$ \001\033[1;34m\002minishell V3 " RESET);
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!minishell(line, &env_lst))
		{
			free(line);
			continue ;
		}
		free(line);
		free_all(getter());
	}
}

void setup_signals_parent(void)
{
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_lst;

	(void)argc;
	(void)argv;
	line = NULL;
	env_lst = init_env(envp);
	env_lst = split_env(env_lst);
	setup_signals_parent();
	setup_minishell(line, env_lst);
	free(env_lst);
}
