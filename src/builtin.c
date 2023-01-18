/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:04:10 by dgioia            #+#    #+#             */
/*   Updated: 2023/01/18 20:03:52 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_exit(t_minishell *mini)
{
	printf("exit\n");
	mini->exit_status = 1;
}

void	get_pwd()
{
	char *curr_pwd;
	
	curr_pwd = getcwd(NULL, 0);
	printf("%s\n", curr_pwd);
}

void	get_echo(char **cmd)
{
	int i;
	int newline;
	
	i = 1;
	newline = 0;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		newline = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if(cmd[i + 1])
			printf(" ");
		i++;
	}
	if(newline == 0)
		printf("\n");
}

int	builtin(t_minishell *mini)
{
	if (!ft_strncmp(mini->full_cmd[0], "echo", 4))
		get_echo(mini->full_cmd);
	else if (!ft_strncmp(mini->full_cmd[0], "cd", 2))
		printf("test cd");
	else if (!ft_strncmp(mini->full_cmd[0], "pwd", 3))
		get_pwd();
	else if (!ft_strncmp(mini->full_cmd[0], "export", 6))
		printf("test export");
	else if (!ft_strncmp(mini->full_cmd[0], "unset", 5))
		printf("test unset");
	else if (!ft_strncmp(mini->full_cmd[0], "env", 3))
		printf("test env");
	else if (!ft_strncmp(mini->full_cmd[0], "exit", 4))
		get_exit(mini);
	else
		return (1);
    return (0);
}