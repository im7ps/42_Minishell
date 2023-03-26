/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 16:22:55 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

int	ft_check_path(t_list **envp)
{
	t_list *env;
	
	env = *envp;
	while (env != NULL)
	{
		if (!(ft_strncmp(env->key, "PATH", 5)))
			return (0);
		env = env->next;
	}
	return (1);
}

int	handle_command(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
    if (handle_builtin(mini, head, envp, pipes, index, cmd_num))
    {
		g_exit_status = 0;
    }
    else
    {
        if (handle_non_builtin(mini, head, envp, pipes, index, cmd_num) == 1)
		{
			g_exit_status = 1;
			return (1);
		}
		else
			g_exit_status = 0;
    }
	return (0);
}

//heredoc
int	ft_heredoc(t_minishell *mini, int **pipes)
{
	int			buffer_size;
	int			fd2;
	int			fd;
	char		*file_content;
	struct 		stat st;
	
	file_content = NULL;
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
		if (!ft_strncmp(file_content, mini->cmd_list->next->cmd_m[0], 3))
		{
			/*parte del programma che legge il contenuto del file, lo salva in una matrice con prima stringa == nome_comando e lo manda in esecuzione*/
			// int i;
			// i = 0;
			// while (mini->cmd_list->cmd_m[i])
			// {
			// 	ft_printf("debug: %s\n", mini->cmd_list->cmd_m[i]);
			// 	i++;
			// }
			//handle_command(mini->cmd_list, &mini->envp_list, pipes, mini->index, mini->cmd_num);
			free(file_content);
			file_content = NULL;
			close(fd2);
			break ;
		}

		fd2 = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (!fd2)
		{
			ft_printf("Error opening the tmp file\n");
			return (1);
		}
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
	int			tmp_exitstatus;

	mini = *minip;
	head = mini->cmd_list;
	if (ft_check_path(envp))
		return (1);

	pid = (int*) malloc (sizeof(int) * mini->cmd_num);
	pipes = (int**) malloc (sizeof(int*) * (mini->cmd_num + 1));

	open_pipes(pipes, mini->cmd_num);
	while(head)
	{
		//handle_command(mini, head, envp, pipes, mini->index, mini->cmd_num);
		if (head->start_red == 0 || head->start_red == 1)
		{
			if (head->final_red == 3)
			{
				if (ft_heredoc(mini, pipes) == 1)
				{
					g_exit_status = 1;
					return (1);
				}
			}
			else if (head->final_red == 5)
			{
				if (ft_redirect_input(mini, head, pipes, mini->index) == 1)
					g_exit_status = 1;
				mini->index++;
			}
			ft_printf("index at command: %d\n", mini->index);
			if (handle_command(mini, head, envp, pipes, mini->index, mini->cmd_num) == 1)
			{
				g_exit_status = 1;
				return (1);
			}
		}
		else if (head->start_red == 2)
		{
			ft_append_output(pipes, head, mini->index);
		}
		else if (head->start_red == 4) //head->start_red == 4 vuol dire esegui una redirection di tipo ">"
		{
			ft_printf("index at redirect output: %d\n", mini->index);
			ft_printf("pipe address: %p\n", pipes[mini->index][0]);
			ft_printf("pipes address: %p\n", pipes);
			ft_redirect_output(pipes, head, mini->index);
		}
		mini->index++;
		head = head->next;
	}
	close_pipes(pipes, mini->cmd_num);
	wait_for_execution(mini->cmd_num, mini->built_in_counter);
	return (0);
}
