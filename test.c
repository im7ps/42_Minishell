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

void	ft_check_redirection(char *cmd)
{
	int		i;
    int     s_quote = 0;
    int     d_quote = 0;
    int     append_o = 0;
    int     red_o = 0;
    int     read_i = 0;
    int     read_i = 0;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			s_quote++;
		if (cmd[i] == '"')
			d_quote++;
		if (cmd[i] == '>' && !(s_quote % 2) && !(d_quote % 2))
		{
			if (i + 2 < ft_strlen(cmd))
			{
				if (cmd[i + 1] == '>' && cmd[i + 2] == ' ')
					append_o++;
			}
			else
				red_o++;
		}
		else if (cmd[i] == '<' && !(s_quote % 2) && !(d_quote % 2))
		{
			if (i + 2 < ft_strlen(cmd))
			{
				if (cmd[i + 1] == '<' && cmd[i + 2] == ' ')
					read_i++;
			}
			else
				red_i++;
		}
		i++;
	}
    if (red_o > 0)
        printf("Nodo %d redirect output %d times\n", i, red_o);
    if (red_i > 0)
        printf("Nodo %d redirect input %d times\n", i, red_i);
    if (append_o > 0)
        printf("Nodo %d append output %d times\n", i, append_o);
    if (read_o > 0)
        printf("Nodo %d read input %d times\n", i, read_i);
}

int main() 
{
    char *str = "echo >> < lel | << grep >";

    ft_check_redirection(str);
}
