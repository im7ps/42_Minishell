/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:13 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/25 18:44:33 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	ft_pipes_single(int **pipes, int index, char **args)
// {
// 	close(pipes[0][0]);
// 	close(pipes[0][1]);
// 	close(pipes[1][0]);
// 	close(pipes[1][1]);	
// }

// void	ft_pipes_first(int **pipes, int index, char **args)
// {
// 	/*int err = 0;
// 	// ft_printf("FIRST\n");

// 	close(pipes[index][0]);

// 	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
// 	if (err == -1)
// 	{
// 		ft_printf("Error using dup2F\n");
// 	}
// 	close(pipes[index + 1][1]);*/
	
// }

// void	ft_pipes_middle(int **pipes, int index, char **args)
// {
// 	char	*input;
// 	int		i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		ft_printf("%s\n", args[i]);
// 		i++;
// 	}
// 	/*int err = 0;
// 	// ft_printf("MIDDLE\n");

// 	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
// 	if (err == -1)
// 	{
// 		ft_printf("Error using dup2M1\n");
// 	}
// 	close(pipes[index + 1][1]);

// 	err = dup2(pipes[index][0], STDIN_FILENO);
// 	if (err == -1)
// 	{
// 		ft_printf("Error using dup2M2\n");
// 	}
// 	close(pipes[index][0]);*/
// 	//read(pipes[index][0], &input, )
// }

// void	ft_pipes_last(int **pipes, int index, char **args)
// {
// 	/*int err = 0;
// 	// ft_printf("LAST\n");
	
// 	close(pipes[index + 1][1]);
// 	err = dup2(pipes[index][0], STDIN_FILENO);
// 	if (err == -1)
// 	{
// 		ft_printf("Error using dup2L\n");
// 	}
// 	close(pipes[index][0]);*/
// 	write(STDOUT_FILENO, "test\n", 5);
// }

// void ft_pipes_builtin(int **pipes, int index, int cmd_num, char **args)
// {
// 		int		i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		ft_printf("%s\n", args[i]);
// 		i++;
// 	}
// 	/*int	i;

// 	i = 0;
// 	while (i < cmd_num + 1)
// 	{
// 		if (i != index)
// 		{
// 			close(pipes[i][0]);
// 		}
// 		if (i != index + 1)
// 		{
// 			close(pipes[i][1]);
// 		}
// 		i++;
// 	}*/

// 	if (cmd_num == 1)
// 	{
// 		ft_printf("single built in\n");
// 		ft_pipes_single(pipes, index, args);
// 	}
// 	else if (index == 0 && cmd_num != 1)
// 	{
// 		ft_printf("first built in\n");
// 		ft_pipes_first(pipes, index, args);
// 	}
// 	else if (index != cmd_num - 1 && index != 0)
// 	{
// 		ft_printf("middle built in\n");
// 		ft_pipes_middle(pipes, index, args);
// 	}
// 	else if (index == cmd_num - 1)
// 	{
// 		ft_printf("last built in\n");
// 		ft_pipes_last(pipes, index, args);
// 	}
// }

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

int	ft_echo(t_minishell *mini, t_list *head, int **pipes, int index, int cmd_num)
{
	int	i;
	int last_arg;
	int	flag_index;
	int	flag_ended;
	int	flag;

	i = 1;
	flag_index = 0;
	flag_ended = 0;

	while (head->cmd_m[i])
	{
		flag = ft_is_flag(head->cmd_m[i]);
		if (flag && flag_ended != 1)
		{
			flag_index = i;
		}
		else if (!flag)
		{
			flag_ended = 1;
		}
		i++;
	}
	last_arg = i;
	i = 1;
	while (head->cmd_m[i])
	{
		if (i > flag_index)
		{
			if (index != cmd_num - 1) // && mini->flush != 1
			{
				if (i != last_arg - 1)
				{
					write(pipes[index + 1][1], head->cmd_m[i], ((ft_strlen(head->cmd_m[i])) * sizeof(char)));
					if (i != last_arg - 2)
					{
						write(pipes[index + 1][1], " ", sizeof(char));
					}
				}
				else
				{
					if (flag_index == 0)
					{
						write(pipes[index + 1][1], "\n", sizeof(char));
					}
				}
			}
			else
			{
				if (ft_is_redirection(head->cmd_m[i]) == 0)
				{
					write(STDOUT_FILENO, head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
					if (i != last_arg - 1)
					{
						write(STDOUT_FILENO, " ", sizeof(char));
					}
					if (flag_index == 0 && i == last_arg - 1)
					{
						write(STDOUT_FILENO, "\n", sizeof(char));
					}
				}
			}
		}
		i++;
	}
	return (0);
}