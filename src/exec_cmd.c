/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:52:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/15 20:09:42 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execute_single(int **pipes, char **args, t_list *head, int cmd_num)
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveS\n");
	return 0;
}

//esegue il primo comando, pipes sono le pipe in cui scrivere l output e scrivere l input, args non viene //utilizzato, head é il mio nodo che contiene tutte le informazioni del comando, cmd_num é il numero dei comandi, index é la posizione del comando nell elenco dei comandi, in questo caso é il primo comando quindi index = 1
int ft_execute_first(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int err;
	char	*file_content;

	ft_printf("Exec first cat\n");
	// read(pipes[index][0], file_content, 12);
	// close(pipes[index][0]);
	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	// close(pipes[index + 1][1]);
	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveF\n");
	return (1);
}

int	ft_execute_middle(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int err = 0;

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M1\n");
	}
	// close(pipes[index + 1][1]);

	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M2\n");
	}
	// close(pipes[index][0]);


	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveM\n");

	return (1);
}


int	ft_execute_last(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int err = 0;

	// close(pipes[index + 1][1]);
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2L\n");
	}
	// close(pipes[index][0]);

	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveL\n");

	return (1);
}

int	ft_execute_command(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	// int i;
	
	// i = 0;
	// while (i < cmd_num + 1)
	// {
	// 	if (i != index)
	// 	{
	// 		close(pipes[i][0]);
	// 	}
	// 	if (i != index + 1)
	// 	{
	// 		close(pipes[i][1]);
	// 	}
	// 	i++;
	// }

	if (cmd_num == 1)
	{
		ft_execute_single(pipes, args, head, cmd_num);
	}
	else if (index == 0 && cmd_num != 1)
	{
		ft_execute_first(pipes, args, head, cmd_num, index);
	}
	else if (index != cmd_num - 1 && index != 0)
	{
		ft_execute_middle(pipes, args, head, cmd_num, index);
	}
	else if (index == cmd_num - 1)
	{
		ft_execute_last(pipes, args, head, cmd_num, index);
	}
	return (1);
}
