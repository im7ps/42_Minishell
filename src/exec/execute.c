/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 14:28:54 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

int	handle_command(t_minishell *mini, t_list *head, t_list **envp, int **pipes)
{
	if (handle_builtin(mini, head, envp, pipes))
	{
		g_exit_status = 0;
	}
	else
	{
		if (handle_non_builtin(mini, head, envp, pipes) == 1)
		{
			return (1);
		}
	}
	return (0);
}

int	ft_init_file(void)
{
	int	fd;

	fd = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
	{
		ft_printf("Error opening the heredoc file\n");
		return (1);
	}
	write(fd, NULL, 1);
	close(fd);
	return (0);
}

//heredoc
int	ft_heredoc(t_minishell *mini, int **pipes, char *str)
{
	int			fd;
	char		*file_content;

	if (ft_init_file())
		return (1);
	while (1)
	{
		file_content = readline("heredoc > ");
		if (!ft_strncmp(file_content, str, ft_strlen(file_content)))
			break ;
		fd = open("heredoc_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (!fd)
		{
			ft_printf("Error opening the heredoc file\n");
			return (1);
		}
		write(fd, file_content, ft_strlen(file_content));
		write(fd, "\n", 1);
		write(pipes[mini->index][1], file_content, ft_strlen(file_content));
		write(pipes[mini->index][1], "\n", 1);
		close(fd);
	}
	return (0);
}

int	ft_red_router(t_minishell	*mini, t_list *head, int **pipes, t_list **envp)
{
	if (head->start_red == 0 || head->start_red == 1)
	{
		if (head->final_red == 3)
		{
			if (ft_heredoc(mini, pipes, head->next->cmd_m[0]) == 1)
				return (1);
		}
		else if (head->final_red == 5)
		{
			if (ft_redirect_input(mini, head, pipes, mini->index) == 1)
				return (1);
		}
		if (handle_command(mini, head, envp, pipes) == 1)
			return (1);
	}
	else if (head->start_red == 2)
	{
		ft_norma_append_out(mini, pipes, head);
	}
	else if (head->start_red == 4)
	{
		ft_norma_redirect_out(mini, pipes, head);
	}
	return (0);
}

int	ft_start_executing(t_minishell **minip, t_list **envp)
{
	t_minishell	*mini;
	t_list		*head;
	int			**pipes;

	mini = *minip;
	head = mini->cmd_list;
	if (mini->input[0] == '\0' || (mini->input[0] != '/' && mini->nopath == 1))
		return (1);
	else if (!ft_dedicated(mini->cmd_list->cmd_m[0]))
		return (0);
	pipes = gc_alloc(&mini->garbage, (sizeof (int *) * (mini->cmd_num + 1)), 0);
	open_pipes(pipes, mini->cmd_num, &mini->garbage);
	while (head)
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
