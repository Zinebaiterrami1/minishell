/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/29 04:45:04 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mimi.h"
#include "../../../includes/minishell.h"

t_lexer	*init_lexer(char *line, t_env **env)
{
	t_lexer	*lexer;

	lexer = gc_malloc(sizeof(t_lexer), getter());
	lexer->line = line;
	lexer->head = NULL;
	lexer->reel_head = NULL;
	lexer->i = 0;
	lexer->c = line[lexer->i];
	lexer->line_size = ft_strlen(line);
	lexer->error = 0;
	lexer->status_d = 0;
	lexer->status_s = 0;
	lexer->env = env;
	return (lexer);
}

void	lexer_skip_white(t_lexer *lexer)
{
	while (lexer->line[lexer->i] == ' ' || lexer->line[lexer->i] == '\t')
		lexer->i++;
}

int	check(char *line)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !d_quotes)
			s_quotes = !s_quotes;
		if (line[i] == '"' && !s_quotes)
			d_quotes = !d_quotes;
		i++;
	}
	if (s_quotes || d_quotes)
		return (1);
	return (0);
}

void	*syntax_error(char *s)
{
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	return (NULL);
}
