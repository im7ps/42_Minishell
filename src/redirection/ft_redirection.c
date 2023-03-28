/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:07:45 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/29 00:48:44 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

//red = 5 "<"
int	ft_redirect_input(t_minishell *mini, t_list *head, int **pipes, int i)
{
	int		fd;
	int		buffer_size;
	char	*file_content;
	struct 	stat st;

	if (head->next != NULL)
	{
		// while (head->next != NULL && head->next->final_red == 5)
		// {
		// 	head = head->next;
		// }
		ft_printf("Sto aprendo: |%s|\n", head->next->cmd_m[0]);
		fd = open(head->next->cmd_m[0], O_RDONLY);
		if (fd < 0)
		{
			g_exit_status = 1;
			return (1);
		}
		if (fstat(fd, &st) == -1)
		{
			return (1);
		}
		buffer_size = st.st_size;
		ft_printf("Len <: %d\n", buffer_size);
		file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
		read(fd, file_content, buffer_size);
		// if (head->next && head->next->final_red != 1)
		// {
			write(pipes[i + 2][1], file_content, buffer_size);
		// }
		// write(pipes[i + 1][1], file_content, buffer_size);
		// write(STDOUT_FILENO, file_content, buffer_size);
		close(fd);
		//head = head->next;
	}
	return (0);	
}

//red = 2 ">>"
int	ft_append_output(int **pipes, t_list *head, int i)
{
	int			buffer_size;
	int			fd;
	char		*file_content;
	struct 		stat st;
	int			j;

	if (fstat(pipes[i][0], &st) == -1)
	{
		return (1);
	}
	buffer_size = st.st_size;

	file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
	read(pipes[i][0], file_content, buffer_size);
	file_content[buffer_size] = '\0';
	fd = open(head->cmd_m[0], O_WRONLY | O_CREAT | O_APPEND, 0644); // apre il file specificato per la scrittura
	if (fd < 0)
	{
		g_exit_status = 1;
		ft_printf("Problems with file opening\n");
		return (1);
	}
	write(fd, file_content, buffer_size);
	write(pipes[i + 1][1], file_content, buffer_size);
	j = 1;
	while (head->cmd_m[j])
	{
		if (ft_is_redirection(head->cmd_m[j]) == 0)
		{
			write(fd, head->cmd_m[j], ft_strlen(head->cmd_m[j]));
			write(pipes[i + 1][1], head->cmd_m[j], ft_strlen(head->cmd_m[j]));
		}
		j++;
	}
	close(fd);
	return (0);
}

//red = 4 ">"
int	ft_redirect_output(int **pipes, t_list *head, int i)
{
	int			buffer_size;
	int			fd;
	char		*file_content;
	struct 		stat st;
	
	int			len;
	int			j;

	//legge 0 da questa pipe
	if (fstat(pipes[i][0], &st) == -1)
	{
		ft_printf("Errore lettura pipe\n");
	}
	buffer_size = st.st_size;
	ft_printf("Len >: %d\n", buffer_size);

	file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
	read(pipes[i][0], file_content, buffer_size);
	file_content[buffer_size] = '\0';
	fd = open(head->cmd_m[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		g_exit_status = 1;
		ft_printf("Problems with file opening\n");
		return (1);
	}
	//ft_printf("Scrivo %s nel file e nella pipe.index: %d\n", file_content, i);
	write(fd, file_content, buffer_size);
	write(pipes[i + 1][1], file_content, buffer_size);
	//write(pipes[i + 2][1], file_content, buffer_size);
	j = 1;
	while (head->cmd_m[j])
	{
		if (ft_is_redirection(head->cmd_m[j]) == 0)
		{
			write(fd, head->cmd_m[j], ft_strlen(head->cmd_m[j]));
			write(pipes[i + 1][1], head->cmd_m[j], ft_strlen(head->cmd_m[j]));
			//write(pipes[i + 2][1], head->cmd_m[j], ft_strlen(head->cmd_m[j]));
		}
		j++;
	}
	close(fd);
	return (0);
}
