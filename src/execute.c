/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/17 20:47:07 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		ft_exec_cmd(t_list	*head, int	attr_num)
{
	const char 	*binpath;
	pid_t		pid1;

	binpath = "/bin/";
	head->cmd_m[0] = ft_strjoin(binpath, head->cmd_m[0]);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
	{
		//we are in the child process
		execve(head->cmd_m[0], head->cmd_m, NULL);
	}
	else
	{
		waitpid(pid1, NULL, 0);	}
	return (0);
}

int	ft_count_commands(t_list **cmd_list)
{
	t_list	*head;
	int		i;

	head = *cmd_list;
	while(head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int ft_start_executing(t_list	**cmd_list)
{
	t_list	*head;
	int		attr_num;

	head = *cmd_list;
	attr_num = ft_count_commands(cmd_list);
	while(head)
	{
		ft_exec_cmd(head, attr_num);
		head = head->next;
	}
	return (0);
}