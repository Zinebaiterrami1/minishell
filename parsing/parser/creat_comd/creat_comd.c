/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_comd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:47:30 by nel-khad          #+#    #+#             */
/*   Updated: 2025/06/23 00:43:21 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_word(t_token_type type)
{
	if (type == T_WORD || type == T_D_COTS || type == T_EXP || type == T_S_COTS)
		return (1);
	return (0);
}

int	is_red(t_token_type type)
{
	if (type == T_RED_OUT || type == T_RED_IN || type == T_RED_OUT_APEND
		|| type == T_HERDOC)
		return (1);
	return (0);
}

static void	add_command(t_command **list, t_command *new)
{
	t_command	*ptr;

	if (new == NULL || !list)
		return ;
	ptr = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (ptr->next_com)
	{
		ptr = ptr->next_com;
	}
	if (ptr)
		ptr->next_com = new;
	return ;
}

t_command	*new_comd(t_command **list, t_token *token)
{
	t_command	*comd;
	t_token		*cur;
	int			count;

	count = 0;
	cur = token;
	comd = gc_malloc(sizeof(t_command), getter());
	while (cur)
	{
		if (is_red(cur->type) && cur->next)
			cur = cur->next->next;
		else
		{
			count++;
			cur = cur->next;
		}
	}
	printf("count = %d\n", count);
	comd->arg = gc_malloc(sizeof(char *) * (count + 1), getter());
	comd->next_com = NULL;
	comd->redir = NULL;
	add_command(list, comd);
	if (comd)
		return (comd);
	return (NULL);
}

void	fill_arg(t_command *comd, int f, t_token *token)
{
	comd->arg[f] = gc_strdup(token->value);
	printf("argg = ___%s\n", token->value);
}
