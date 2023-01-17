/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgioia <dgioia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:04:10 by dgioia            #+#    #+#             */
/*   Updated: 2023/01/16 22:48:22 by dgioia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_pwd()
{
	char *curr_pwd;
	
	curr_pwd = getcwd(NULL, 0);
	printf("%s\n", curr_pwd);

	return (0);
}

int	get_echo(char *cmd)
{
	/* 	echo test -> test\n
		echo -n test -> test
		echo -nnnnn test -> test
		echo -n -n -n test -> test
		echo -n echo -n -> echo -n
		echo echo -n -> echo -n\n
	*/
	
	return (0);
}

int	builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		get_echo(cmd);
	if (!ft_strncmp(cmd, "cd", 2))
		printf("test cd");
	if (!ft_strncmp(cmd, "pwd", 3))
		get_pwd();
	if (!ft_strncmp(cmd, "export", 6))
		printf("test export");
	if (!ft_strncmp(cmd, "unset", 5))
		printf("test unset");
	if (!ft_strncmp(cmd, "env", 3))
		printf("test env");
	if (!ft_strncmp(cmd, "exit", 4))
		printf("test exit");
	return (0);
}