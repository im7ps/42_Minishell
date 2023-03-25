/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:29 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/25 18:37:50 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_list *head, char **cmd_m, int **pipes, int index)
{
	char 	*cwd;
	int		i;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		if (head->final_red != 0)
		{
			write(pipes[index + 1][1], cwd, (sizeof(char) * (ft_strlen(cwd) + 1)));
		}
		else if (head->final_red == 0)
		{
			ft_printf("Im writing to stdout\n");
			write(STDOUT_FILENO, cwd, (sizeof(char) * (ft_strlen(cwd) + 1)));
		}
	}
	else
	{
		return (1);
	}
	return (0);
}