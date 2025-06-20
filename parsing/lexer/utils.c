/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:35:56 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/19 22:00:35 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mimi.h"
#include "../../includes/minishell.h"

void	print_listt(t_garbage *token)
{
	while (token)
	{
		printf("%p === ", token->adress);
		token = token->next;
	}
	printf("\n");
}

// int is_special(char c)
// {
//     if(ft_strchr(" ><    '\"$|",
// c))//////////????????????????????????????????????????
//         return(1);
//     if (c == ' ' || c == '\t' || c == '\''
//         || c == '"' || c == '|' || c == '&' || c == '$'
//         || c == '>' || c == '<' || c == '\0')
//         return(1);
//     return(0);
// }

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
void	*syntax_error(int i)
{
	printf("syntax error %d \n", i);
	return (NULL);
}