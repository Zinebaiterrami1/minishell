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

int	ft_exit(char **args)
{
	long	code;

	write(2, "exit\n", 5);
	if (!args[1])
		exit(g_last_status);
	if (!ft_is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atoi(args[1]);
	exit((unsigned char)code);
}