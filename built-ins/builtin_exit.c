/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:22 by zait-err          #+#    #+#             */
/*   Updated: 2025/05/15 21:08:24 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/mini.h"

static int	ft_is_numeric(char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// int	ft_exit(char **args)
// {
// 	long	code;

// 	write(2, "exit\n", 5);
// 	if (!args[1])
// 		exit(0);
// 	if (!ft_is_numeric(args[1]))
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n", args[1]);
// 		exit(255);
// 	}
// 	if (args[2])
// 	{
// 		printf("minishell: exit: too many arguments\n");
// 		return (1);
// 	}
// 	code = ft_atoi(args[1]);
// 	exit((unsigned char)code);
// }


int ft_exit(char **args)
{
	int code;
	int arg_count;

	arg_count = 0;
	write(2, "exit\n", 5);
	while(args[arg_count])
		arg_count++;
	if(arg_count == 1)
		exit(0);
	if(!ft_is_numeric(args[1]))
	{
			printf("Error: numeric argument required\n");
			exit(255);
	}
	if(arg_count > 2) 
	{
		printf("Error:too many arguments\n");
		return (1);
	}
	code = ft_atoi(args[1]);
	exit(code % 256);
}