/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:07:45 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/18 20:07:48 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//red = 5 "<"
int	ft_redirect_input(t_list *head, int **pipes, int i)
{
	int		fd;
	int		buffer_size;
	char	*file_content;
	struct stat st;

	//se il comando ha < come redirection, deve prima far scrivere il contenuto del file in una pipe, e poi eseguire il comando su quella pipe
	ft_printf("Sto redirectando il contenuto del file nella pipe\n");
	if (head->next != NULL)
	{
		fd = open(head->next->cmd_m[0], O_RDONLY); // apre il file specificato per la lettura
		if (fd < 0)
		{
			ft_printf("Problems with file opening\n");
			return (1);
		}
		// ottieni la dimensione del contenuto del file
		if (fstat(fd, &st) == -1)
		{
			perror("fstat");
			exit(EXIT_FAILURE);
		}
		buffer_size = st.st_size;

		file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
		read(fd, file_content, buffer_size);
		write(pipes[i + 1][1], file_content, buffer_size);
		close(fd);
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
	
	// ottieni la dimensione del contenuto della pipe
	if (fstat(pipes[i][0], &st) == -1)
	{
		perror("fstat");
		exit(EXIT_FAILURE);
	}
	buffer_size = st.st_size;

	file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
	read(pipes[i][0], file_content, buffer_size);
	file_content[buffer_size] = '\0';

	fd = open(head->cmd_m[0], O_WRONLY | O_CREAT | O_APPEND, 0644); // apre il file specificato per la scrittura
	if (fd < 0)
	{
		ft_printf("Problems with file opening\n");
		return (1);
	}
	write(fd, file_content, buffer_size);
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

	// ottieni la dimensione del contenuto della pipe
	if (fstat(pipes[i][0], &st) == -1)
	{
		perror("fstat");
		exit(EXIT_FAILURE);
	}
	buffer_size = st.st_size;
	file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
	read(pipes[i][0], file_content, buffer_size);
	file_content[buffer_size] = '\0';
	fd = open(head->cmd_m[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); // apre il file specificato per la scrittura
	if (fd < 0)
	{
		ft_printf("Problems with file opening\n");
		return (1);
	}
	write(fd, file_content, buffer_size);
	close(fd);
	return (0);
}
