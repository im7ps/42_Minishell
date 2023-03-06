/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:13 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/06 18:47:17 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pipes_single(int **pipes, int index)
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);	
}

void	ft_pipes_first(int **pipes, int index)
{
	int err = 0;
	// ft_printf("FIRST\n");

	close(pipes[index][0]);

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	close(pipes[index + 1][1]);
}

void	ft_pipes_middle(int **pipes, int index)
{
	int err = 0;
	// ft_printf("MIDDLE\n");

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M1\n");
	}
	close(pipes[index + 1][1]);

	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M2\n");
	}
	close(pipes[index][0]);
}

void	ft_pipes_last(int **pipes, int index)
{
	int err = 0;
	// ft_printf("LAST\n");
	
	close(pipes[index + 1][1]);
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2L\n");
	}
	close(pipes[index][0]);
}

void ft_pipes_builtin(int **pipes, int index, int cmd_num)
{
	int	i;

	i = 0;
	while (i < cmd_num + 1)
	{
		if (i != index)
		{
			close(pipes[i][0]);
		}
		if (i != index + 1)
		{
			close(pipes[i][1]);
		}
		i++;
	}

	if (cmd_num == 1)
	{
		ft_printf("single built in\n");
		ft_pipes_single(pipes, index);
	}
	else if (index == 0 && cmd_num != 1)
	{
		ft_printf("first built in\n");
		ft_pipes_first(pipes, index);
	}
	else if (index != cmd_num - 1 && index != 0)
	{
		ft_printf("middle built in\n");
		ft_pipes_middle(pipes, index);
	}
	else if (index == cmd_num - 1)
	{
		ft_printf("last built in\n");
		ft_pipes_last(pipes, index);
	}
}

int	ft_is_flag(char *cmd_arg)
{
	int	i;

	if (cmd_arg[0] != '-')			//se il primo char non é un - sicuramente non é una flag
		return (0);
	i = 1;
	while (cmd_arg[i])
	{
		if (cmd_arg[i] != 'n')		//se un char dell argomento non é n non é una flag
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_list *head, int **pipes, int index, int cmd_num)
{
	int	i;
	int	flag_index;
	int	flag_ended;

	i = 1;
	flag_index = 0;
	flag_ended = 0;
	// ft_printf("ECHO INDEX %i of %i\n", index, cmd_num);
	ft_printf("Pipes address %p\n", pipes);
	ft_pipes_builtin(pipes, index, cmd_num);
	while (head->cmd_m[i])
	{
		//ft_printf("THIS %s\n", head->cmd_m[i]);
		if ((ft_is_flag(head->cmd_m[i])) && flag_ended != 1)
		{
			//ft_printf("I found a flag --> |%s|\n", head->cmd_m[i]);
			flag_index = i + 1;
		}
		else if (!(ft_is_flag(head->cmd_m[i])))
		{
			//ft_printf("The flag ended at %i element --> |%s|\n", flag_index, head->cmd_m[i]);
			flag_ended = 1;
		}
		i++;
	}
	// write(STDOUT_FILENO, "test", 4);
	write(pipes[index + 1][1], "test\n", 5);
	//ft_printf("KISS: %s\n", head->cmd_m[flag_index]);
	if (flag_index == 0)
	{
		ft_printf("0 flags found\n");
	}
	return (0);
}