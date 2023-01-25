/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/25 17:41:13 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		ft_exec_cmd(t_list	*head, int	cmd_num)
{
	//fd[0] = read from the pipe, fd[1] = write into the pipe
	int fd[2];
	int	pid1;
	int	pid2;
	// char *args[] = {"echo", "-n", "test\n", NULL};

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		//we are in the child process
		execve("/bin/echo", &head->cmd_m[0], NULL);
		//tutto quello che viene dopo execve viene eseguito solo dal parent
	}
	//andiamo al prossimo nodo della lista
	head = head->next;
	//un nuovo processo? una nuova fork
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/echo", &head->cmd_m[0], NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
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
	int		cmd_num;

	head = *cmd_list;
	cmd_num = ft_count_commands(cmd_list);
	while(head)
	{
		ft_exec_cmd(head, cmd_num);
		head = head->next;
	}
	return (0);
}