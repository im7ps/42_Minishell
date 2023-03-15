/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/15 22:45:23 by sgerace          ###   ########.fr       */
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

int ft_start_executing(t_list	**cmd_list, int cmd_num, t_list **envp)
{
	t_list		*head;
	int			*pid;
	int			i;
	int 		**pipes;
	int			not_built_in_counter;
	int			builtin_res;
	char		**args;

	// struct 		stat st;
	// int			buffer_size;
	// int			fd;
	// char		*file_content;

	pid = (int*) malloc (sizeof(int) * cmd_num);
	pipes = (int**) malloc (sizeof(int*) * (cmd_num + 1));

	head = *cmd_list;

	not_built_in_counter = 0;
	i = 0;
    while(i < cmd_num + 1) 
	{
		pipes[i] = (int *) malloc (sizeof(int) * 2);
        if (pipe(pipes[i]) == -1) 
		{
            ft_printf("Error with creating pipe\n");
            return 1;
        }
		i++;
    }

	i = 0;
	while(head)
	{
		//o é il primo argomento della pipeline, quindi un comando, o ha la pipe come redirection quindi é un comando
		if (head->red == -1 || head->red == 1)
		{
			int	command_red = ft_redirection_type(head->cmd_m);
			//gestisci comandi del tipo cat < file.txt
			if (command_red == 5)
			{
				ft_redirect_input(head, pipes, i);
				i++;
			}
			//gestisci HEREDOC
			else if (command_red == 3)
			{
				int			buffer_size;
				int			fd2;
				char		*file_content;
				struct 		stat st;
				
				file_content = NULL;
				while (!(ft_strncmp(file_content, "EOF", 3)))
				{
					write(1, "\n", 1);
					rl_on_new_line();
					rl_replace_line("heredoc>", 0);
					rl_redisplay();

					fd2 = open("heredoc_tmp.txt", O_RDWR | O_CREAT, 0644);
					if (!fd2)
					{
						ft_printf("Error opening the tmp file\n");
						return (1);
					}
					dup2(fd2, STDIN_FILENO);
					
					if (fstat(fd2, &st) == -1)
					{
						ft_printf("Error using fstat\n");
						return (1);
					}

					buffer_size = st.st_size;
					file_content = (char *) malloc (sizeof(char) * (buffer_size + 1));
					read(fd2, file_content, buffer_size);
					// if (!ft_strncmp(file_content, "EOF", 3))
					// {
					// 	free(file_content);
					// 	file_content = NULL;
					// 	close(fd2);
					// 	break ;
					// }
					// write(fd2, file_content, buffer_size);

					// free(file_content);
					// file_content = NULL;
					close(fd2);
				}
				
			}
			ft_printf("Im here!!!\n");
			builtin_res = is_builtin(head, envp, pipes, i, cmd_num);
			if (builtin_res)
			{
				not_built_in_counter++;
				ft_printf("Eseguito comando builtin\n");
			}
			else
			{
				//se ritorna NULL vuol dire che il comando non esiste o non si hanno gli accessi adatti
				head->cmd_m[0] = ft_trypath(head->cmd_m[0], envp);
				if (head->cmd_m[0] == NULL)
				{
					ft_printf("Command not found\n");
					head = head->next;
				}
				if (head->next != NULL)
				{
					head->next->red = ft_redirection_type(head->cmd_m);
				}
				head->cmd_m = ft_delete_redirection(head->cmd_m);
				pid[i] = fork();
				if (pid[i] < 0)
					return (2);

				if (pid[i] == 0)
				{
					if (ft_execute_command(pipes, args, head, cmd_num, i) == 1)
						return (1);
					return (0);
				}
			}
		}
		else if (head->red == 2)
		{
			ft_append_output(pipes, head, i);
		}
		else if (head->red == 4)
		{
			ft_redirect_output(pipes, head, i);
		}
		else if (head->red == 5)
		{
			ft_printf("Sempre luii\n");
		}
		i++;
		if (head->next != NULL && builtin_res)
		{
			head->next->red = ft_redirection_type(head->cmd_m);
		}
		head = head->next;
	}

	if (cmd_num != 1)		//le pipes sono già state chiuse in ft_execute_single
	{
		i = 0;
		while (i < cmd_num + 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
	}

	i = 0;
	while (i < cmd_num - not_built_in_counter)
	{
		wait(NULL);
		i++;
	}

	i = 0;
    while(i < cmd_num + 1) 
	{
		//free(pipes[i]);
		i++;
    }
	//free(pipes);
	//free(pid);
	return (0);
}
