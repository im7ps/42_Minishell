#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_list
{
	int		pipe;
	int		red_i;
	int		red_o;
	int		read_i;
	int		append_o;
	int		s_quote;
	int		d_quote;
	char	**cmd_m;
	struct s_list	*next;
}	t_list;

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*stack;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)								//se si vuole iniziare a copiare la stringa da un indice che e' superiore alla lunghezza della stringa per evitare l overflow si mette l indice alla fine della stringa
		start = ft_strlen(s);
	if (ft_strlen(s) <= start + len)						//se si parte da un inizio valido ma si vogliono copiare troppi caratteri si finirebbe in buffer overflow, il massimo che si puo' fare e' copiare len caratteri (fai un test per capire meglio)
		len = ft_strlen(s) - start;
	stack = (char *) malloc (sizeof(char) * len + 1);
	if (!stack)
		return (NULL);
	while (len--)
		stack[i++] = s[start++];
	stack[i] = '\0';
	return (stack);
}

char	**fill_m(const char *s, char c, char	**matrix, int num_w)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (j < num_w)									//il numero di volte che la stringa deve essere splittata
	{
		while (s[i] == c)								//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				i++;
		while (s[i + len] != c && s[i + len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
			len++;
		if (len != 0)									//se hai 0 char che ti indicano il punto di troncamento vuol dire che non devi troncare mai la stringa, in caso contrario...
		{
			matrix[j] = ft_substr(s, i, len);			//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
			j++;
		}
		i += len;								//i + len e' il trick per evitare di ricominciare la ricerca ogni volta dall inizio della stringa anziche' ricominciare dal char dopo il troncamento
		len = 0;
	}
	return (matrix);
}

int	count_w(char *str, char c)
{
	int	num;
	int	toggle;

	num = 0;
	toggle = 0;
	while (*str)
	{
		if (*str != c && toggle == 0 && *str != '\0')	//se siamo in una parola (*str != c), non l abbiamo ancora contata nel numero delle parole (toggle == 0) e la stringa non e' finita (*str != '\0')
		{
			toggle = 1;									//se incontri altri caratteri sappi che sei ancora nella stringa, non splittare
			num++;
		}
		else if (*str == c)								//dopo che trovi la corrispondenza con il carattere esegui un troncamento (toggle == 0)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ft_split(char const *s, char c)
{
	int		num_w;
	char	**matrix;

	if (!s)
		return (NULL);
	num_w = count_w((char *)s, c);								//capisci in quanti "pezzi" verra' divisa la stringa originale
	matrix = (char **) malloc(sizeof(char *) * (num_w + 1));	//occhio alle parentesi...
	if (!matrix)
		return (NULL);
	matrix[num_w] = NULL;
	matrix = fill_m(s, c, matrix, num_w);
	return (matrix);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst != NULL)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
	else
		(*lst) = new;
}


t_list	*ft_lstnew(char *str)
{
	t_list	*nodo;

	nodo = (t_list *) malloc (sizeof(t_list));
	if (nodo == NULL)
		return (NULL);
	nodo->cmd_m = ft_split(str, ' ');
	nodo->next = NULL;
	return (nodo);
}

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
    t_list *new_node;
	int		i;
	
	i = 0;
	while (full_cmd[i])
	{
		new_node = ft_lstnew(full_cmd[i]);
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	return ;
}

void	ft_exec_first(t_list **cmdl, int fd[2])
{
	t_list	*head;
	char	*input;
	size_t	rd;

	head = *cmdl;
	input = (char *) malloc (sizeof(char) * 6);

	if (pipe(fd) == -1)
		return ;
	//dup2 mette in collegamento due estremità delle pipes, in questo caso sto collegando STDIN a fd[0]
	dup2(fd[0], STDIN_FILENO);
	//legge "echo test e lo salva su fd[0]"
	read(fd[0], &input, 10);
	printf("NOW %s\n", input);
	close(fd[0]);
	//calcolare l output modificato dal comando, metterlo in &input e scriverlo su fd[1]
	//write(fd[1], &input, (sizeof(char) * ft_strlen(head->cmd_m[1])));
	close(fd[1]);
	//execve("/bin/echo", &head->cmd_m[0], NULL);
}



int	ft_execute(t_list **cmdl, int	cmd_num)
{
	//a seconda del comando da eseguire il parent si dovrà comportare in maniera diversa
	//quindi prima gli faccio capire se è un comando built in o no, poi gli dico quale comando è
	//di preciso e lo rimando ad un execute_command fatto apposta
}

int	ft_count_commands(t_list **cmd_list)
{
	t_list	*head;
	int		i;

	i = 0;
	head = *cmd_list;
	while(head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int main(int argc, char **argv) 
{
	t_list *cmd_l = NULL;
	int	cmd_num = 0;
	char *str = "echo test";
    char *str1 = "echo test | echo testone | echo testardo";

	if (argc != 1)
	{
		char **full_cmd = ft_split(argv[1], '|');
		ft_create_list(&cmd_l, full_cmd);
		cmd_num = ft_count_commands(&cmd_l);
		while (cmd_l)
		{
			ft_execute(&cmd_l, cmd_num);
			cmd_l = cmd_l->next;
		}
	}
	return (0);
}

/* #include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];
    char variable[100];
    pipe(pipefd);
    dup2(pipefd[1], 1);
    write(pipefd[1], "input_string", sizeof("input_string"));
    dup2(pipefd[0], 0);
    read(pipefd[0], buffer, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';
    strcpy(variable, buffer);
    printf("The input is: %s\n", variable);
    fflush(stdout);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
} */
