/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:13 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:44:37 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_flag(char *cmd_arg)
{
	int	i;

	if (cmd_arg[0] != '-')
		return (0);
	i = 1;
	while (cmd_arg[i])
	{
		if (cmd_arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo_flag(char **cmd_m, t_echo *echo)
{
	int	i;
	int	flag_ended;
	int	flag;

	i = 1;
	flag = 0;
	flag_ended = 0;
	echo->flag_index = 0;
	while (cmd_m[i])
	{
		flag = ft_is_flag(cmd_m[i]);
		if (flag && flag_ended != 1)
		{
			echo->flag_index = i;
		}
		else if (!flag)
		{
			flag_ended = 1;
		}
		i++;
	}
	return (i);
}

void	ft_echo_write(int fd, t_echo echo, char *str)
{
	if (echo.i > echo.flag_index)
	{
		if (echo.i != echo.len)
		{
			write(fd, str, ((ft_strlen(str)) * sizeof(char)));
			if (echo.i != echo.len - 1)
			{
				write(fd, " ", sizeof(char));
			}
		}
	}
}

int	ft_echo(t_list *head, int **pipes, int index)
{
	t_echo	echo;
	int		fd;

	if (ft_count_rows(head->cmd_m) == 1 && head->final_red == 0)
	{
		write(STDOUT_FILENO, "\n", sizeof(char));
		return (0);
	}
	echo.len = ft_echo_flag(head->cmd_m, &echo);
	echo.i = 1;
	while (head->cmd_m[echo.i])
	{
		if (head->final_red != 0)
		{
			fd = pipes[index + 1][1];
		}
		else if (head->final_red == 0)
			fd = STDOUT_FILENO;
		ft_echo_write(fd, echo, head->cmd_m[echo.i]);
		echo.i++;
	}
	if (echo.flag_index == 0)
		write(fd, "\n", sizeof(char));
	return (0);
}
