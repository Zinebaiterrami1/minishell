/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:38:54 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 02:17:06 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cases(t_command *cmd, t_env *env)
{
	char	*pathcmd;
	struct stat file_stat;
	
	pathcmd = NULL;
	if (ft_strchr(cmd->arg[0], '/'))
	{	printf("am here\n");
		if(stat(cmd->arg[0], &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd(cmd->arg[0], 1);
			ft_putstr_fd(" :Is a directory\n", 1);
			g_exit_status = 126;
			exit(g_exit_status);
		}
		else if (access(cmd->arg[0], F_OK | X_OK) == 0)
			pathcmd = cmd->arg[0];
	}
	else if (ft_strcmp(".", cmd->arg[0]) == 0)
	{
		printf(".: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		g_exit_status = 2; 
		exit(g_exit_status);
	}	
	else
		pathcmd = search_cmd(cmd, env);

	if (!pathcmd)
	{
		// printf("minishell: %s command not found jhgjgjhhjghg\n", cmd->arg[0]);
		fprintf(stderr, "DEBUG: command not found: '%s'\n", cmd->arg[0]);
		// g_exit_status = 127;
		// exit(g_exit_status);
			fprintf(stderr, "[DEBUG] exiting with 127\n");
		exit(127);
	}
	execve(pathcmd, cmd->arg, get_envp(env));
	perror("minishell");
	fprintf(stderr, "DEBUG: execve failed, exiting with 126\n");
	exit(126);
}