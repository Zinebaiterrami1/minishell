/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:25:02 by zait-err          #+#    #+#             */
/*   Updated: 2025/06/25 13:25:33 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sig_handler_heredoc(int signal)
{
    (void)signal;
	write(1, "\n", 1); 
	g_exit_status = 130;
	exit(g_exit_status);                                                                                                                                                                                                                                                                                                                                                                                      
}

void setup_signals_heredoc(void)
{
	signal(SIGINT, sig_handler_heredoc);
}
