/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/22 17:32:22 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_commands(t_list **cmd_list)
{
	t_list	*head;
	int		i;

	i = 0;
	head = *cmd_list;
	while(head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	ft_execute_single(int *fd, char **args, t_list *head)
{
	close(fd[0]);
	close(fd[1]);
	execve(head->cmd_m[0], args, NULL);
	return 0;
}


int ft_execute_first(int *fd, char **args, t_list *head)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(head->cmd_m[0], args, NULL);
	return (0);
}

int	ft_execute_middle(int *fd, char **args, t_list *head)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execve(head->cmd_m[0], args, NULL);
	return (0);
}

int	ft_execute_last(int *fd, char **args, t_list *head)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execve(head->cmd_m[0], args, NULL);
	return 0;
}

int ft_start_executing(t_list	**cmd_list)
{
	t_list	*head;
	int		attr_num;
	int		*pid;
	int		i;
	int 	fd[2];
	const char 	*binpath;

	binpath = "/bin/";
	head = *cmd_list;
	attr_num = ft_count_commands(cmd_list);
	pid = (int*) malloc (sizeof(int) * attr_num);

	if (pipe(fd) == -1) 
	{
        return (1);
    }

	i = 0;
	while(head)
	{
		head->cmd_m[0] = ft_strjoin(binpath, head->cmd_m[0]);
		char *args[] = {head->cmd_m[0], head->cmd_m[1], NULL};
		pid[i] = fork();
		if (pid[i] < 0)
			return (2);
		if (pid[i] == 0)
		{
			if (i == 0 && attr_num == 1)
			{
				ft_execute_single(fd, args, head);
			}
			else if (i == 0)
			{
				ft_execute_first(fd, args, head);
			}
			else if (i != 0 && i != attr_num - 1)
			{
				ft_execute_middle(fd, args, head);
			}
			else if (i == attr_num - 1)
			{
				ft_execute_last(fd, args, head);
			}
		}
		i++;
		head = head->next;
	}
	i = 0;
	while (i < attr_num)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}