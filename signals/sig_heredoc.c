/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:25:02 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/24 02:21:47 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sig_handler_heredoc(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();                                                                                                                                                                                                                                                                                                                                                                                             
}

void setup_signals_heredoc(void)
{
    struct sigaction sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
