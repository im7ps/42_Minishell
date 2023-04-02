/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:49:13 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 11:01:38 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

int	ft_set_exit_status(int value)
{
	if (value == 1)
		g_exit_status = 1;
	else if (value == 256)
		g_exit_status = 1;
	else if (value == 2)
		g_exit_status = 130;
	else if (value == 0)
		g_exit_status = 0;
	return (g_exit_status);
}

int	wait_for_execution(int cmd_num, int built_in_counter)
{
	int	i;

	i = 0;
	while (i < cmd_num - built_in_counter)
	{
		waitpid(-1, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
		{
			WEXITSTATUS(g_exit_status);
		}
		i++;
	}
	return (0);
}
