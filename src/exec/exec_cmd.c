/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:52:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/29 00:45:07 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int g_exit_status;

int	wait_for_execution(int cmd_num, int built_in_counter) 
{
    int i = 0;
    while (i < cmd_num - built_in_counter)
	{
		waitpid(-1, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
		{
			//printf("Exit status del processo figlio: %d\n", WEXITSTATUS(g_exit_status));
			WEXITSTATUS(g_exit_status);
		}
        i++;
    }
	return (0);
}

int	ft_execute_single(int **pipes, t_list *head, int cmd_num)
{
	ft_printf("Single command: %s\n", head->cmd_m[0]);
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	if (execve(head->cmd_m[0], head->cmd_m, NULL) == -1)
		g_exit_status = 1;
	ft_printf("Problems with execveS\n");
	g_exit_status = 127;
	return 0;
}

int	ft_exec_redinput(int fd, t_list *head, int **pipes, int i)
{
	int err;

	//ft_printf("Il comando |%s| legge da |%s|\n", head->cmd_m[0], head->next->cmd_m[0]);
	fd = open(head->next->cmd_m[0], O_RDONLY);
	if (!fd)
	{
		ft_printf("Error opening file\n");
	}
	err = dup2(fd, STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2F2\n");
	if (head->next->final_red == 2 || head->next->final_red == 4 || head->next->final_red == 1)
	{
		err = dup2(pipes[i + 1][1], STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
			return (1);
		}
	}
	close(fd);
	return (0);
}

void	ft_exec_redheredoc(int fd, t_list *head, int **pipes, int i)
{
	int	err;

	fd = open("heredoc_tmp.txt", O_RDONLY);
	if (!fd)
	{
		ft_printf("Error opening file\n");
	}
	err = dup2(fd, STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2F2\n");
	if (head->next->final_red == 2 || head->next->final_red == 4 || head->next->final_red == 1)
	{
		err = dup2(pipes[i + 1][1], STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
		}
	}
	close(fd);
}

void	ft_exec_redout(int fd, t_list *head)
{
	int	err;

	//ft_printf("Opening this file: %s\n", head->next->cmd_m[0]);
	fd = open(head->next->cmd_m[0], O_RDWR);
	err = dup2(fd, STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	close(fd);
}

void	ft_exec_redout_v(int fd, t_list *head, int **pipes, int i)
{
	int	err;

	//ft_printf("Final red: %d\n", head->next->final_red);
	if (head->next->final_red == 2 || head->next->final_red == 4 || head->next->final_red == 1)
	{
		err = dup2(pipes[i + 1][1], STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
		}
	}
}

void ft_exec_basered(int **pipes, int i)
{
	int err;

	err = dup2(pipes[i + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
}

//esegue il primo comando, pipes sono le pipe in cui scrivere l output e scrivere l input, args non viene //utilizzato, head é il mio nodo che contiene tutte le informazioni del comando, cmd_num é il numero dei comandi, index é la posizione del comando nell elenco dei comandi, in questo caso é il primo comando quindi index = 1
int ft_execute_first(t_minishell *mini, int **pipes, t_list *head, int cmd_num, int index)
{
	int		err;
	char	*file_content;
	int 	i;
	
	int	fd;

	if (head->final_red == 1)
	{
		//ft_exec_redout_v(fd, head, pipes, index);
		ft_exec_basered(pipes, index);
	}
	else if (head->final_red == 5)
	{
		ft_exec_redinput(fd, head, pipes, index);
	}
	else if (head->final_red == 3)
	{
		ft_exec_redheredoc(fd, head, pipes, index);
	}
	else if (head->final_red == 2 || head->final_red == 4)
	{
		ft_exec_redout(fd, head);
	}
	else
	{
		ft_exec_redout_v(fd, head, pipes, index);
	}
	i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (execve(head->cmd_m[0], head->cmd_m, NULL) == -1)
		g_exit_status = 1;
	ft_printf("Problems with execveF\n");
	g_exit_status = 127;
	return (1);
}

int	ft_execute_middle(t_minishell *mini, int **pipes, t_list *head, int cmd_num, int index)
{
	int err = 0;
	int	fd;

	//ft_printf("Final red middle: %d\n", head->final_red);
	if (head->final_red == 3 || head->final_red == 5)
	{
		//ft_printf("Sto cambiando stdin e stdout\n");
		struct 		stat st;
		int			buffer_size;

		if (fstat(pipes[index][0], &st) == -1)
		{
			ft_printf("Error calculating size\n");
		}
		buffer_size = st.st_size;
		ft_printf("Size: %d\n", buffer_size);
		err = dup2(pipes[index][0], STDIN_FILENO);
		if (err == -1)
			ft_printf("Error using dup2M2\n");
		if (head->next && head->next->final_red != 0)
		{
			err = dup2(pipes[index + 2][1], STDOUT_FILENO);
			if (err == -1)
				ft_printf("Error using dup2M\n");
		}
	}
	else
	{
		err = dup2(pipes[index][0], STDIN_FILENO);
		if (err == -1)
			ft_printf("Error using dup2M2\n");
		err = dup2(pipes[index + 1][1], STDOUT_FILENO);
		if (err == -1)
			ft_printf("Error using dup2M\n");
	}
	int i = 0;
	while (i < mini->cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	g_exit_status = 1;
	return (1);
}


int	ft_execute_last(int **pipes, t_list *head, int cmd_num, int index)
{
	int err;
	int i;
	int	fd;

	err = 0;
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2L\n");
	if (head->final_red == 2 || head->final_red == 4)
	{
		ft_printf("Opening this file: %s\n", head->next->cmd_m[0]);
		fd = open(head->next->cmd_m[0], O_RDWR);
		err = dup2(fd, STDOUT_FILENO);
		if (err == -1)
		{
			ft_printf("Error using dup2F\n");
		}
		close(fd);
	}
	i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (execve(head->cmd_m[0], head->cmd_m, NULL) == -1)
		g_exit_status = 1;
	ft_printf("Problems with execveL\n");
	g_exit_status = 127;
	return (1);
}

int	ft_execute_command(t_minishell *mini, int **pipes, t_list *head, int cmd_num, int index)
{
	if (head->start_red == 0 && head->final_red == 0)
	{
		if(ft_execute_single(pipes, head, cmd_num))
			return (0);
	}
	else if (head->start_red == 0)
	{
		//ft_printf("First command: %s\n", head->cmd_m[0]);
		if (ft_execute_first(mini, pipes, head, cmd_num, index))
			return (0);
	}
	else if (head->start_red != 0 && head->final_red != 0)
	{
		ft_printf("Middle command: %s\n", head->cmd_m[0]);
		if (ft_execute_middle(mini, pipes, head, cmd_num, index))
			return (0);
	}
	else if (head->final_red == 0)
	{
		//ft_printf("Last command: %s\n", head->cmd_m[0]);
		if (ft_execute_last(pipes, head, cmd_num, index))
			return (0);
	}
	return (1);
}


// funzione per gestire i comandi non built-in
int handle_non_builtin(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
    pid_t pid;

	//ft_printf("index non builtin: %d del comando num: %s\n", index, head->cmd_m[0]);

	if (head->cmd_m[0][0] != '/')
	{
		head->cmd_m[0] = ft_trypath(&mini, head->cmd_m[0], envp);
	}
    if (head->cmd_m[0] == NULL)
    {
        ft_printf("Command not found\n");
		g_exit_status = 127;
        return (127);
    }
    pid = fork();
    if (pid < 0)
        return (2);
    if (pid == 0)
    {
        if (ft_execute_command(mini, pipes, head, cmd_num, index))
            return (1);
        return (0);
    }
	return (0);
}