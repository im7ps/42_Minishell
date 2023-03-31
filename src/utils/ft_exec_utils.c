/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:46:48 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 20:54:08 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exec_redinput(t_list *head, int **pipes, int i)
{
	int	err;
	int	fd;

	fd = open(head->next->cmd_m[0], O_RDONLY);
	if (!fd)
	{
		ft_printf("Error opening file\n");
	}
	err = dup2(fd, STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2F2\n");
	if (head->next->final_red == 2 || head->next->final_red == 4 || \
		head->next->final_red == 1)
	{
		err = dup2(pipes[i + 1][1], STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
			return (1);
		}
	}
	close(fd);
	return (0);
}

void	ft_exec_redheredoc(t_list *head, int **pipes, int i)
{
	int	err;
	int	fd;

	fd = open("heredoc_tmp.txt", O_RDONLY);
	if (!fd)
	{
		ft_printf("Error opening file\n");
	}
	err = dup2(fd, STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2F2\n");
	if (head->next->final_red == 2 || head->next->final_red == 4 || \
		head->next->final_red == 1)
	{
		err = dup2(pipes[i + 1][1], STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
		}
	}
	close(fd);
}

void	ft_exec_redout(t_list *head)
{
	int	err;
	int	fd;

	fd = open(head->next->cmd_m[0], O_RDWR);
	err = dup2(fd, STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	close(fd);
}

void	ft_exec_redout_v(t_list *head, int **pipes, int i)
{
	int	err;

	if (head->next->final_red == 2 || head->next->final_red == 4 \
		|| head->next->final_red == 1)
	{
		err = dup2(pipes[i + 1][1], STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
		}
	}
}

void	ft_exec_basered(int **pipes, int i)
{
	int	err;

	err = dup2(pipes[i + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
}
