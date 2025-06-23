/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 00:11:51 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	skip_dollar(char *line, int *i)
{
	while (line[*i] == '$' && line[*i + 1] && line[*i + 1] == '$')
		(*i) += 2;
	return ;
}

static char	*get_expand(char *line, int *i, t_herdoc *herdoc)
{
	char	*val;

	val = NULL;
	(*i)++;
	if (ft_isdigit(line[*i]))
		return ((*i)++, NULL);
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		val = ft_strjoin(val, create_string(line[*i]));
		(*i)++;
	}
	return (get_exp(val, herdoc->env));
}

char	*herdoc_expand(char *line, t_herdoc *herdoc)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			skip_dollar(line, &i);
			if (line[i] == '$')
				s = ft_strjoin(s, get_expand(line, &i, herdoc));
		}
		else
			while (line[i] && line[i] != '$')
			{
				s = ft_strjoin(s, create_string(line[i]));
				i++;
			}
	}
	return (s);
}
