/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:52:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/18 20:06:41 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Funzione esterna per la parte 3
void wait_for_execution(int cmd_num, int built_in_counter) 
{
    int i = 0;
    while (i < cmd_num - built_in_counter) 
	{
        wait(NULL);
        i++;
    }
}

int	ft_execute_single(int **pipes, t_list *head, int cmd_num)
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveS\n");
	return 0;
}

//esegue il primo comando, pipes sono le pipe in cui scrivere l output e scrivere l input, args non viene //utilizzato, head é il mio nodo che contiene tutte le informazioni del comando, cmd_num é il numero dei comandi, index é la posizione del comando nell elenco dei comandi, in questo caso é il primo comando quindi index = 1
int ft_execute_first(int **pipes, t_list *head, int cmd_num, int index)
{
	int err;
	char	*file_content;

	ft_printf("Exec first cat\n");
	// read(pipes[index][0], file_content, 12);
	// close(pipes[index][0]);
	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	// close(pipes[index + 1][1]);
	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveF\n");
	return (1);
}

int	ft_execute_middle(int **pipes, t_list *head, int cmd_num, int index)
{
	int err = 0;

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M1\n");
	}
	// close(pipes[index + 1][1]);

	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M2\n");
	}
	// close(pipes[index][0]);


	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveM\n");

	return (1);
}


int	ft_execute_last(int **pipes, t_list *head, int cmd_num, int index)
{
	int err = 0;

	// close(pipes[index + 1][1]);
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2L\n");
	}
	// close(pipes[index][0]);

	int i = 0;
	while (i < cmd_num + 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	execve(head->cmd_m[0], head->cmd_m, NULL);
	ft_printf("Problems with execveL\n");

	return (1);
}

int	ft_execute_command(int **pipes, t_list *head, int cmd_num, int index)
{
	if (cmd_num == 1)
	{
		if(ft_execute_single(pipes, head, cmd_num))
			return (0);
	}
	else if (index == 0 && cmd_num != 1)
	{
		if (ft_execute_first(pipes, head, cmd_num, index))
			return (0);
	}
	else if (index != cmd_num - 1 && index != 0)
	{
		if (ft_execute_middle(pipes, head, cmd_num, index))
			return (0);
	}
	else if (index == cmd_num - 1)
	{
		if (ft_execute_last(pipes, head, cmd_num, index))
			return (0);
	}
	return (1);
}


// funzione per gestire i comandi non built-in
int handle_non_builtin(t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
    pid_t pid;

    head->cmd_m[0] = ft_trypath(head->cmd_m[0], envp);
    if (head->cmd_m[0] == NULL)
    {
        ft_printf("Command not found\n");
        if (head->next != NULL)
            head = head->next;
        else
            return (1);
    }
    if (head->next != NULL)
        head->next->red = ft_redirection_type(head->cmd_m);
    head->cmd_m = ft_delete_redirection(head->cmd_m);
    pid = fork();
    if (pid < 0)
        return (2);
    if (pid == 0)
    {
        if (ft_execute_command(pipes, head, cmd_num, index))
            return (1);
        return (0);
    }
	return (0);
}