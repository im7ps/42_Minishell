/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:52:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 15:52:39 by sgerace          ###   ########.fr       */
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

//esegue il primo comando, pipes sono le pipe in cui scrivere l output e scrivere l input, args non viene //utilizzato, head é il mio nodo che contiene tutte le informazioni del comando, cmd_num é il numero dei comandi, index é la posizione del comando nell elenco dei comandi, in questo caso é il primo comando quindi index = 1
int ft_execute_first(t_minishell *mini, int **pipes, t_list *head, int cmd_num, int index)
{
	int		err;
	char	*file_content;
	int 	i;

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
		ft_printf("Error using dup2F\n");
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
	
	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
			ft_printf("Error using dup2M\n");
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2M2\n");

	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (execve(head->cmd_m[0], head->cmd_m, NULL) == -1)
		g_exit_status = 1;
	ft_printf("Problems with execveM\n");
	g_exit_status = 127;
	return (1);
}


int	ft_execute_last(int **pipes, t_list *head, int cmd_num, int index)
{
	int err;
	int i;

	err = 0;
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
		ft_printf("Error using dup2L\n");
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
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR)
		printf("failed to register interrupt\n");
	if (head->start_red == 0 && head->final_red == 0)
	{
		if(ft_execute_single(pipes, head, cmd_num))
			return (0);
	}
	else if (head->start_red == 0)
	{
		if (ft_execute_first(mini, pipes, head, cmd_num, index))
			return (0);
	}
	else if (head->start_red != 0 && head->final_red != 0)
	{
		if (ft_execute_middle(mini, pipes, head, cmd_num, index))
			return (0);
	}
	else if (head->final_red == 0)
	{
		if (ft_execute_last(pipes, head, cmd_num, index))
			return (0);
	}
	return (1);
}


// funzione per gestire i comandi non built-in
int handle_non_builtin(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
    pid_t pid;

	//ft_printf("Il comando non builtin testato é: %s\n", head->cmd_m[0]);
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