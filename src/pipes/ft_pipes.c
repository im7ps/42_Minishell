/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:04:37 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/01 00:01:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exec_closepipes(int **pipes, int cmd_num)
{
	int	i;

	i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

// Funzione esterna per la parte 1
void	open_pipes(int **pipes, int cmd_num, t_garbage **garbage)
{
	int	i;

	i = 0;
	while (i < cmd_num + 1)
	{
		pipes[i] = gc_alloc(garbage, (sizeof(int) * 2), 0);
		if (pipe(pipes[i]) == -1)
		{
			ft_printf("Error with creating pipe\n");
			return ;
		}
		i++;
	}
}

// Funzione esterna per la parte 2
void	close_pipes(int **pipes, int cmd_num)
{
	int	i;

	i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
