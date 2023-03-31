/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:52:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:38:32 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execute_single(int **pipes, t_list *head)
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	if (execve(head->cmd_m[0], head->cmd_m, NULL) == -1)
		ft_printf("Problems with execveS\n");
	return (0);
}

int	ft_execute_first(int **pipes, t_list *head, int cmd_num, int index)
{
	int	i;

	if (head->final_red == 1)
	{
		ft_exec_basered(pipes, index);
	}
	else if (head->final_red == 5)
	{
		ft_exec_redinput(head, pipes, index);
	}
	else if (head->final_red == 3)
	{
		ft_exec_redheredoc(head, pipes, index);
	}
	else if (head->final_red == 2 || head->final_red == 4)
	{
		ft_exec_redout(head);
	}
	else
	{
		ft_exec_redout_v(head, pipes, index);
	}
	i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (execve(head->cmd_m[0], head->cmd_m, NULL) == -1)
		ft_printf("Problems with execveF\n");
	return (1);
}

int	ft_execute_middle(t_minishell *mini, int **pipes, t_list *head, int index)
{
	int	err;
	int	i;

	err = 0;
	if (head->final_red == 3 || head->final_red == 5)
	{
		err = dup2(pipes[index][0], STDIN_FILENO);
		if (err == -1)
			ft_printf("Error using dup2M2\n");
		if (head->next && head->next->final_red != 0)
		{
			err = dup2(pipes[index + 2][1], STDOUT_FILENO);
			if (err == -1)
				ft_printf("Error using dup2M\n");
		}
	}
	else
	{
		err = dup2(pipes[index][0], STDIN_FILENO);
		if (err == -1)
			ft_printf("Error using dup2M2\n");
		err = dup2(pipes[index + 1][1], STDOUT_FILENO);
		if (err == -1)
			ft_printf("Error using dup2M\n");
	}
	i = 0;
	while (i < mini->cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	return (1);
}

int	ft_execute_last(int **pipes, t_list *head, int cmd_num, int index)
{
	int	err;
	int	i;
	int	fd;

	err = 0;
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2L\n");
	if (head->final_red == 2 || head->final_red == 4)
	{
		ft_printf("Opening this file: %s\n", head->next->cmd_m[0]);
		fd = open(head->next->cmd_m[0], O_RDWR);
		err = dup2(fd, STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
		}
		close(fd);
	}
	i = 0;
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

int	ft_execute_command(t_minishell *mini, int **pipes, t_list *head)
{
	if (head->start_red == 0 && head->final_red == 0)
	{
		if (ft_execute_single(pipes, head))
			return (0);
	}
	else if (head->start_red == 0)
	{
		if (ft_execute_first(pipes, head, mini->cmd_num, mini->index))
			return (0);
	}
	else if (head->start_red != 0 && head->final_red != 0)
	{
		if (ft_execute_middle(mini, pipes, head, mini->index))
			return (0);
	}
	else if (head->final_red == 0)
	{
		if (ft_execute_last(pipes, head, mini->cmd_num, mini->index))
			return (0);
	}
	return (1);
}
