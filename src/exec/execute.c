/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/29 00:40:18 by sgerace          ###   ########.fr       */
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

int ft_init_file()
{
	int	fd;

	fd = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
	{
		ft_printf("Error opening the tmp file\n");
		return (1);
	}
	write(fd, NULL, 1);
	close(fd);
	return (0);
}

//heredoc
int	ft_heredoc(t_minishell *mini, t_list *head, int **pipes, char *str)
{
	int			buffer_size;
	int			fd;
	char		*file_content;
	struct 		stat st;

	if (ft_init_file())
		return (1);
	while (1)
	{
		file_content = readline("heredoc > ");
		if (!ft_strncmp(file_content, str, ft_strlen(file_content)))
		{
			break ;
		}
		fd = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (!fd)
		{
			ft_printf("Error opening the tmp file\n");
			return (1);
		}
		write(fd, file_content, ft_strlen(file_content));
		write(fd, "\n", 1);
		write(pipes[mini->index][1], file_content, ft_strlen(file_content));
		write(pipes[mini->index][1], "\n", 1);
		free(file_content);
		close(fd);
	}
	//head->final_red = 6;
	return (0);
}

int	ft_red_router(t_minishell	*mini, t_list *head, int **pipes, t_list **envp)
{
	//ft_printf("Il comando %s ha la prima red = %d\n", head->cmd_m[0], head->start_red);
	if (head->start_red == 0 || head->start_red == 1)
	{
		if (head->final_red == 3)
		{
			if (ft_heredoc(mini, head, pipes, head->next->cmd_m[0]) == 1)
				return (1);
		}
		else if (head->final_red == 5)
		{
			if (ft_redirect_input(mini, head, pipes, mini->index) == 1)
				return (1);
			//mini->index++;
		}
		//esegui ls, scrivi il suo contenuto sulla pipe anziché lo STDOUT
		if (handle_command(mini, head, envp, pipes, mini->index, mini->cmd_num) == 1)
		{
			ft_printf("Here2!\n");
			return (1);
		}
		//ft_printf("Here3!\n");
	}
	else if (head->start_red == 2)
	{
		waitpid(0, &g_exit_status, 0);
		mini->built_in_counter++;
		ft_append_output(pipes, head, mini->index);
	}
	//leggi il contenuto della pipe scritta da ls e scrivilo sul file
	else if (head->start_red == 4)
	{
		waitpid(0, &g_exit_status, 0);
		mini->built_in_counter++;
		ft_redirect_output(pipes, head, mini->index);
	}
	return (0);
}

int ft_start_executing(t_minishell **minip, t_list	**cmd_list, t_list **envp)
{
	t_minishell	*mini;
	t_list		*head;
	int			i;
	int 		**pipes;

	mini = *minip;
	head = mini->cmd_list;
	if (ft_check_path(envp))
		return (1);
	pipes = (int**) malloc (sizeof(int*) * (mini->cmd_num + 1));
	open_pipes(pipes, mini->cmd_num);
	while(head)
	{
		if (ft_red_router(mini, head, pipes, envp))
			return (1);
		mini->index++;
		head = head->next;
	}
	close_pipes(pipes, mini->cmd_num);
	wait_for_execution(mini->cmd_num, mini->built_in_counter);
	return (0);
}
