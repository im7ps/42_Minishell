/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:29 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/10 18:30:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(char **cmd_m, int **pipes, int index)
{
	char 	cwd[1024];
	int		i;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (!ft_strncmp(cmd_m[i - 1], "|", 1))
		{
			write(pipes[index + 1][1], cwd, (sizeof(char) * (ft_strlen(cwd) + 1)));
		}
		else
		{
			write(STDOUT_FILENO, cwd, (sizeof(char) * (ft_strlen(cwd) + 1)));
		}
	}
	else
	{
		return (1);
	}
	return (0);
}