/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/23 23:49:07 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execute_single(int **pipes, char **args, t_list *head, int cmd_num)
{
	char *arg1s[] = {"/usr/bin/echo", "SINGLE", "SIUUM", NULL};
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	execve("/usr/bin/echo", arg1s, NULL);
	ft_printf("Problems with execveS\n");
	return 0;
}


int ft_execute_first(int **pipes, char **args, t_list *head, int cmd_num)
{
	int i;
	
	i = 0;
	ft_printf("FIRST\n");
    while (i < cmd_num + 1)
	{
		if (i != cmd_num)
		{
        	close(pipes[i][0]);
		}
        if (i != 0) 
		{
            close(pipes[i][1]);
        }
		i++;
    }
	close(pipes[cmd_num][0]);
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	ft_printf("F%sF\n", head->cmd_m[0]);
	execve(head->cmd_m[0], args, NULL);
	ft_printf("Problems with execveF\n");
	return (1);
}

int	ft_execute_middle(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int i;
	
	i = 0;
	ft_printf("MIDDLE\n");
    while (i < cmd_num + 1)
	{
		if (i != index)
		{
        	close(pipes[i][0]);
		}
        if (i != index + 1)
		{
            close(pipes[i][1]);
        }
		i++;
    }
	dup2(pipes[index + 1][1], STDOUT_FILENO);
	close(pipes[index + 1][1]);
	dup2(pipes[index][0], STDIN_FILENO);
	close(pipes[index][0]);
	ft_printf("M%sM\n", head->cmd_m[0]);
	execve(head->cmd_m[0], args, NULL);
	ft_printf("Problems with execveM\n");
	return (1);
}

int	ft_execute_last(int **pipes, char **args, t_list *head, int cmd_num)
{
	int i;
	
	i = 0;
	ft_printf("LAST\n");
    while (i < cmd_num + 1)
	{
		if (i != cmd_num)
		{
        	close(pipes[i][0]);
		}
        if (i != 0) 
		{
            close(pipes[i][1]);
        }
		i++;
    }
	close(pipes[0][1]);
	dup2(pipes[0][1], STDIN_FILENO);
	close(pipes[cmd_num][0]);
	ft_printf("L%sL\n", head->cmd_m[0]);
	execve(head->cmd_m[0], args, NULL);
	ft_printf("Problems with execveL\n");
	return (1);
}

int ft_start_executing(t_list	**cmd_list, int cmd_num)
{
	t_list	*head;
	int		*pid;
	int		i;
	int		cmd_num_plus;
	int 	**pipes;
	const char 	*binpath;

	//binpath = "/bin/"; //flag per MACOS
	binpath = "/usr/bin/"; //flag per ubuntu
	head = *cmd_list;
	pid = (int*) malloc (sizeof(int) * cmd_num);
	pipes = (int**) malloc (sizeof(int) * cmd_num);

	cmd_num_plus = cmd_num + 1;
	i = 0;
    while(i < cmd_num_plus) 
	{
		pipes[i] = (int *) malloc (sizeof(int) * 2);
        if (pipe(pipes[i]) == -1) 
		{
            ft_printf("Error with creating pipe\n");
            return 1;
        }
		i++;
    }

	i = 0;
	while(head)
	{
		head->cmd_m[0][ft_strlen(head->cmd_m[0]) - 2] = '\0';
		head->cmd_m[0] = ft_strjoin(binpath, head->cmd_m[0]);
		char *args[] = {head->cmd_m[0], head->cmd_m[1], NULL}; //da mettere in un while per unire tutti i vari argomenti in args

		pid[i] = fork();
		if (pid[i] < 0)
			return (2);

		if (pid[i] == 0)
		{
			if (i == 0 && cmd_num == 1)
			{
				ft_execute_single(pipes, args, head, cmd_num);
			}
			else if (i == 0 && cmd_num != 1)
			{
				if (ft_execute_first(pipes, args, head, cmd_num) == 1)
					return (1);
			}
			else if (i != 0 && i != cmd_num - 1)
			{
				if (ft_execute_middle(pipes, args, head, cmd_num, i) == 1)
					return (1);
			}
			else if (i == cmd_num - 1 && i != 0)
			{
				if (ft_execute_last(pipes, args, head, cmd_num) == 1)
					return (1);
			}
			return (0);
		}
		i++;
		head = head->next;
	}

		i = 0;
		while (i < cmd_num)
		{
			wait(NULL);
			i++;
		}
		
		if (cmd_num != 1)		//le pipes sono già state chiuse in ft_execute_single
		{
			i = 0;
			while (i < cmd_num_plus)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				ft_printf("Ho chiuso pip[%d][0] e pip[%d][1]\n", i, i);
				i++;
			}
		}

	return (0);
}