/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:13 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/07 20:15:41 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pipes_single(int **pipes, int index, char **args)
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);	
}

void	ft_pipes_first(int **pipes, int index, char **args)
{
	/*int err = 0;
	// ft_printf("FIRST\n");

	close(pipes[index][0]);

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	close(pipes[index + 1][1]);*/
	
}

void	ft_pipes_middle(int **pipes, int index, char **args)
{
	char	*input;
	int		i;

	i = 0;
	while (args[i])
	{
		ft_printf("%s\n", args[i]);
		i++;
	}
	/*int err = 0;
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
	close(pipes[index][0]);*/
	//read(pipes[index][0], &input, )
}

void	ft_pipes_last(int **pipes, int index, char **args)
{
	/*int err = 0;
	// ft_printf("LAST\n");
	
	close(pipes[index + 1][1]);
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2L\n");
	}
	close(pipes[index][0]);*/
	write(STDOUT_FILENO, "test\n", 5);
}

void ft_pipes_builtin(int **pipes, int index, int cmd_num, char **args)
{
		int		i;

	i = 0;
	while (args[i])
	{
		ft_printf("%s\n", args[i]);
		i++;
	}
	/*int	i;

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
	}*/

	if (cmd_num == 1)
	{
		ft_printf("single built in\n");
		ft_pipes_single(pipes, index, args);
	}
	else if (index == 0 && cmd_num != 1)
	{
		ft_printf("first built in\n");
		ft_pipes_first(pipes, index, args);
	}
	else if (index != cmd_num - 1 && index != 0)
	{
		ft_printf("middle built in\n");
		ft_pipes_middle(pipes, index, args);
	}
	else if (index == cmd_num - 1)
	{
		ft_printf("last built in\n");
		ft_pipes_last(pipes, index, args);
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
	int last_arg;
	int	flag_index;
	int	flag_ended;

	i = 1;
	flag_index = 0;
	flag_ended = 0;
	// ft_printf("ECHO INDEX %i of %i\n", index, cmd_num);
	//ft_printf("Pipes address %p\n", pipes);
	//ft_pipes_builtin(pipes, index, cmd_num, args);
	while (head->cmd_m[i])
	{
		//ft_printf("THIS %s\n", head->cmd_m[i]);
		if ((ft_is_flag(head->cmd_m[i])) && flag_ended != 1)
		{
			//ft_printf("I found a flag --> |%s|\n", head->cmd_m[i]);
			flag_index = i;
		}
		else if (!(ft_is_flag(head->cmd_m[i])))
		{
			//ft_printf("The flag ended at %i element --> |%s|\n", flag_index, head->cmd_m[i]);
			flag_ended = 1;
		}
		i++;
	}
	last_arg = i;
	if (flag_index == 0)
	{
		//ft_strjoin(head->cmd_m[last_arg - 1], '\n');
		head->cmd_m[last_arg - 1][ft_strlen(head->cmd_m[last_arg - 1])] = '\n';
	}
	if (!(ft_strncmp(head->cmd_m[last_arg - 1], "|", 1)))
	{
		ft_printf("Found: %s\n", head->cmd_m[last_arg - 1]);
		head->cmd_m[last_arg - 1][ft_strlen(head->cmd_m[last_arg - 1])] = '\0';
	}
	i = 1;
	while (head->cmd_m[i])
	{
		if (i > flag_index)
		{
			//ft_printf("Current arg -%s-\n", head->cmd_m[last_arg - 1]);
			if (index != cmd_num - 1)
			{
				if (i != last_arg - 1)
				{
					ft_printf("|%s|\n", head->cmd_m[i]);
					write(pipes[index + 1][1], head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
					//write(pipes[index + 1][1], " ", sizeof(char));
				}
				/*else
				{
					if (flag_index == 0)
					{
						write(pipes[index + 1][1], "\n", sizeof(char));
					}
				}*/
			}
			else
			{
				//if (i != last_arg - 1)
				//{
					write(STDOUT_FILENO, head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
					//write(pipes[index + 1][1], " ", sizeof(char));
				//}
				/*else
				{
					if (flag_index == 0)
					{
						write(STDOUT_FILENO, "\n", sizeof(char));
					}
				}*/
			}
			/*if (cmd_num == 1)
			{
				ft_printf("Here!\n");
				write(STDOUT_FILENO, head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
			}
			else if (index == 0 && cmd_num != 1)
			{
				ft_printf("Here!2\n");
				//read(pipes[index][0], head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
				//dup2(pipes[index + 1][1], STDOUT_FILENO);
				write(pipes[index + 1][1], head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
			}
			else if (index != 0 && index != cmd_num - 1)
			{
				ft_printf("Here!3\n");
				//dup2(pipes[index + 1][1], STDOUT_FILENO);
				write(pipes[index + 1][1], head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
			}
			else if (index == cmd_num - 1)
			{
				ft_printf("Here!4\n");
				write(STDOUT_FILENO, head->cmd_m[i], (ft_strlen(head->cmd_m[i]) * sizeof(char)));
			}*/
		}
		i++;
	}
	// write(STDOUT_FILENO, "test", 4);
	//ft_printf("KISS: %s\n", head->cmd_m[flag_index]);
	return (0);
}