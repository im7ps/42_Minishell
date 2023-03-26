/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:29 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 00:09:05 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_list *head, char **cmd_m, int **pipes, int index)
{
	char 	*cwd;
	int		i;
	int		fd;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	if (head->final_red != 0)
		fd = pipes[index + 1][1];
	else
		fd = STDOUT_FILENO;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(fd, cwd, (sizeof(char) * (ft_strlen(cwd))));
		write(fd, "\n", 1);
	}
	else
		return (1);
	return (0);
}