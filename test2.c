//caso con 1 comando
//fork
//figlio leggi da STDIN esegue comando e scrive su pipefd[1]
//padre legge da pipefd[0] e scrivi su STDOUT

//caso con n comandi
//fork
//figlio legge da STDIN esegue comando e scrive su pipefd[1]
//while (n > 0)
//{
//padre legge da pipefd[0] e scrivi su pipefd[1]
//fork
//figlio legge da pipefd[0] esegue comando e scrive output su pipefd[1]
//}
//padre legge da pipefd[1] e scrive su STDOUT

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

int main(int argc, char **argv) 
{
	int fd[2];
	char *input;
	char rbuf[100];
	char wbuf[100];
	int id;
	int	i;

	while (1)
	{
		input = readline("minishell> ");
		if (pipe(fd) == -1)
		{
			printf("Pipe error\n");
			return (1);
		}
		id = fork();
		if (id == 0)
		{
			close(fd[0]);
			write(fd[1], input, ft_strlen(input));
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			read(fd[0], wbuf, sizeof(wbuf));
			printf("Got from child: %s\n", wbuf);
			close(fd[0]);
			wait(NULL);
		}
	}
}