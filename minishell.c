/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:03:05 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/28 16:09:14 by zait-err         ###   ########.fr       */
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

static void	setup_minishell(char *line, t_env *env_lst)
{
	while (1)
	{
		setup_signals_parent();
		line = readline(PINK "$ \001\033[1;34m\002minishell V3 " RESET);
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			printf("clean1\n");
			ft_clean(&env_lst);
			free_all(getter());
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
		printf("clean2\n");
		ft_clean(&env_lst);
		free_all(getter());
	}		
}


void	luna_nouss(void)
{
	printf("\033[1;35m"); // Bold magenta
	printf("🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸\n");
	printf("██╗     ██╗   ██╗███╗   ██╗ █████╗     ███╗   ██╗ ██████╗ ██╗   ██╗███████╗███████╗\n");
	printf("██║     ██║   ██║████╗  ██║██╔══██╗    ████╗  ██║██╔═══██╗██║   ██║██╔════╝██╔════╝\n");
	printf("██║     ██║   ██║██╔██╗ ██║███████║    ██╔██╗ ██║██║   ██║██║   ██║███████╗███████╗\n");
	printf("██║     ██║   ██║██║╚██╗██║██╔══██║    ██║╚██╗██║██║   ██║██║   ██║╚════██ ╚════██║\n");
	printf("███████╗╚██████╔╝██║ ╚████║██║  ██║    ██║ ╚████║╚██████╔╝╚██████╔╝███████╗███████║\n");
	printf("╚══════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝    ╚═╝  ╚═══╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝\n");
	printf("                    🌺 WELCOME TO LUNA&NOUSS SHELL 🌺                     \n");
	printf("🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸🌼🌷🌸\n");
	printf("\033[0m");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_lst;

	(void)argc;
	(void)argv;
	line = NULL;
	luna_nouss();
	env_lst = init_env(envp);
	env_lst = split_env(env_lst);
	// setup_signals_parent();
	setup_minishell(line, env_lst);
}
