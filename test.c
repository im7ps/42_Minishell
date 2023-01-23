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

char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);

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



// void	ft_check_redirection(char *cmd)
// {
// 	int		i;
//     int     s_quote = 0;
//     int     d_quote = 0;
//     int     append_o = 0;
//     int     red_o = 0;
//     int     read_i = 0;
//     int     read_i = 0;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'')
// 			s_quote++;
// 		if (cmd[i] == '"')
// 			d_quote++;
// 		if (cmd[i] == '>' && !(s_quote % 2) && !(d_quote % 2))
// 		{
// 			if (i + 2 < ft_strlen(cmd))
// 			{
// 				if (cmd[i + 1] == '>' && cmd[i + 2] == ' ')
// 					append_o++;
// 			}
// 			else
// 				red_o++;
// 		}
// 		else if (cmd[i] == '<' && !(s_quote % 2) && !(d_quote % 2))
// 		{
// 			if (i + 2 < ft_strlen(cmd))
// 			{
// 				if (cmd[i + 1] == '<' && cmd[i + 2] == ' ')
// 					read_i++;
// 			}
// 			else
// 				red_i++;
// 		}
// 		i++;
// 	}
//     if (red_o > 0)
//         printf("Nodo %d redirect output %d times\n", i, red_o);
//     if (red_i > 0)
//         printf("Nodo %d redirect input %d times\n", i, red_i);
//     if (append_o > 0)
//         printf("Nodo %d append output %d times\n", i, append_o);
//     if (read_o > 0)
//         printf("Nodo %d read input %d times\n", i, read_i);
// }

// void ft_addback_node(t_list **cmd_list, char *cmd)
// {
// 	t_list *current;

//     if (*cmd_list == NULL) 
// 	{
//         *cmd_list = new_node;
//     } 
// 	else
// 	{
// 		while ((*cmd_list) != NULL)
// 		{
// 			(*cmd_list) = (*cmd_list)->next;
// 			//(*cmd_list)->next = NULL;
// 		}
// 		(*cmd_list) = new_node;
//     }
// }

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	int		i;
	int		j;
    t_list *new_node;
	
	i = 0;
	while (full_cmd[i])
	{
		new_node = (t_list *)malloc(sizeof(t_list));
		new_node->cmd_m = ft_split(full_cmd[i], ' ');
		new_node->next = NULL;
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	while (*cmd_list)
	{
		j = 0;
		while ((*cmd_list)->cmd_m[j])
		{
			printf("%s\n", (*cmd_list)->cmd_m[j]);
			j++;
		}
		(*cmd_list) = (*cmd_list)->next;
	}
	return ;
}

int main() 
{
    char *str = "prova 1 ses | provolone 2 seven | alleluja";
	char **full_cmd = ft_split(str, '|');
	t_list *cmd_l;

	ft_create_list(&cmd_l, full_cmd);
}
