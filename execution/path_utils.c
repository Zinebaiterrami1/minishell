/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:13:35 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/30 12:57:21 by nel-khad         ###   ########.fr       */
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

static void	helper(t_command *cmd, t_env *env)
{
	t_pipes	p;

	p.nb_cmd = 1;
	ignore_signals();
	p.pid = fork();
	if (p.pid == 0)
	{
		setup_signals_child();
		if (open_file(cmd) == -1)
		{
			ft_clean(&env);
			exit(g_exit_status = 1);
		}
		handle_cases(cmd, env);
		ft_clean(&env);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	wait_children(&p);
}

void	execute_externals(t_command *cmd, t_env *env)
{
	if ((!cmd || !cmd->arg || !cmd->arg[0]) && cmd->redir)
	{
		if (open_file(cmd) == -1)
		{
			g_exit_status = 1;
			return ;
		}
		else
		{
			open_file(cmd);
			g_exit_status = 1;
			return ;
		}
	}
	else if (cmd && cmd->arg && cmd->arg[0] && ft_strlen(cmd->arg[0]) >= 1)
		helper(cmd, env);
}
