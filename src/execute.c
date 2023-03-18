/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/18 21:05:15 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_command(t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
    if (handle_builtin(head, envp, pipes, index, cmd_num))
    {
        ft_printf("\nEseguito comando builtin\n");
    }
    else
    {
        handle_non_builtin(head, envp, pipes, index, cmd_num);
    }
}

//heredoc
int	ft_heredoc()
{
	int			buffer_size;
	int			fd2;
	int			fd;
	char		*file_content;
	struct 		stat st;
	
	file_content = NULL;
	//elimina il contenuto precedente dal file heredoc_tmp
	fd = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
	{
		ft_printf("Error opening the tmp file\n");
		return (1);
	}
	write(fd, NULL, 1);
	close(fd);
	while (1)
	{
		//salva la stringa scritta dall utente
		file_content = readline("heredoc > ");
		if (!ft_strncmp(file_content, "EOF", 3))
		{
			free(file_content);
			file_content = NULL;
			close(fd2);
			break ;
		}
	
		//apri il file in cui scrivere l input dell utente
		fd2 = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (!fd2)
		{
			ft_printf("Error opening the tmp file\n");
			return (1);
		}
		//scrivi nel file la stringa senza cancellare quello che c'era prima
		write(fd2, file_content, ft_strlen(file_content));
		write(fd2, "\n", 1);

		free(file_content);
		file_content = NULL;
		close(fd2);
	}
	return (0);
}

int ft_start_executing(t_minishell **minip, t_list	**cmd_list, t_list **envp)
{
	t_minishell	*mini;
	t_list		*head;
	int			*pid;
	int			i;
	int 		**pipes;

	mini = *minip;
	head = mini->cmd_list;

	pid = (int*) malloc (sizeof(int) * mini->cmd_num);
	pipes = (int**) malloc (sizeof(int*) * (mini->cmd_num + 1));

	open_pipes(pipes, mini->cmd_num);

	while(head)
	{
		//se == 0 é il primo argomento della pipeline, se == 1 é subito dopo una pipe, in entrambi i casi deve essere eseguito un comando
		if (head->start_red == 0 || head->start_red == 1)
		{
			//nel caso > e >> l output va comunque scritto sulle pipes e poi letto da quelle pipes, quindi non cambia rispetto a |, rimangono il caso final == 3 e final == 5
			if (head->final_red == 3)
			{
				ft_heredoc();
			}
			else if (head->final_red == 5)
			{
				ft_redirect_input(head, pipes, mini->index);
				mini->index++;
			}
			handle_command(head, envp, pipes, mini->index, mini->cmd_num);
		}

		else if (head->start_red == 2)
		{
			ft_append_output(pipes, head, mini->index);
		}
		else if (head->start_red == 4)
		{
			ft_redirect_output(pipes, head, mini->index);
		}
		//la gestione degli argomenti pipeline che iniziano con 3 o 5 é stata gestita nell if con 0 o 1, cioé quello dei comandi
		else if (head->start_red == 3 || head->start_red == 5)
		{
			ft_printf("Giá gestito i guessss\n");
		}
		mini->index++;
		head = head->next;
	}
	close_pipes(pipes, mini->cmd_num);
	wait_for_execution(mini->cmd_num, mini->built_in_counter);
	return (0);
}
