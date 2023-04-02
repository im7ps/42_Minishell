/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:23:06 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 12:40:24 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_norma_append_out(t_minishell	*mini, int	**pipes, t_list	*head)
{
	waitpid(0, &g_exit_status, 0);
	mini->built_in_counter++;
	ft_append_output(pipes, head, mini->index, 1);
}

void	ft_norma_redirect_out(t_minishell	*mini, int	**pipes, t_list	*head)
{
	waitpid(0, &g_exit_status, 0);
	mini->built_in_counter++;
	ft_redirect_output(pipes, head, mini->index, 1);
}

int	ft_open_fd_a(t_list *head, char *file_content)
{
	int	fd;

	fd = open(head->cmd_m[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		free(file_content);
		return (1);
	}
	return (fd);
}

int	ft_open_fd_t(t_list *head, char *file_content)
{
	int	fd;

	fd = open(head->cmd_m[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(file_content);
		return (1);
	}
	return (fd);
}

int	ft_calc_buffsize(int **pipes, int i)
{
	struct stat	st;
	int			buffer_size;

	if (fstat(pipes[i][0], &st) == -1)
	{
		return (1);
	}
	buffer_size = st.st_size;
	return (buffer_size);
}
