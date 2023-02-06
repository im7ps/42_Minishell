#include <stdio.h>
#include <stdlib.h>
#include "./inc/minishell.h"
#include "libft/libft.h"

int	ft_strlen1(const char *s)
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

char    *ft_expander_helper(char *input)
{
    int     i;
    char    *tmp;

    i = 0;
    while (((input[i] > 60 && input[i] < 90) || input[i] == 95) && input[i] != '\0')
    {
        i++;
    }
    // tmp = (char *) malloc (sizeof(char) * i + 1);
    printf("%d\n", i);
    return (input);
}

/*  
*   ft_dollar_expander: 
*   se trovi il dollaro confronta con strncmp ogni key trovata nei nodi della lista envp, se trovi una corrispondenza prosegui
*   e modifica il campo input togliendo la key e inserendo al suo posto il value
*/
char	*ft_dollar_expander1(char *input)
{
	int	i;
    int len;

    len = ft_strlen1(input);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
		{
			if (i + 1 < len)
            {
                i++;
                if (!((input[i] > 65 && input[i] < 90) || input[i] == 95))
                    return (NULL);
                input = ft_expander_helper(input + i);
            }
		}
	}
	return (input);
}

int main(int argc, char *argv[], char *envp[])
{
    char **env;
    int i;
    char *str;

    str = "asd $_PATH__AUT $2 $! asfas\n";

    ft_dollar_expander1(str);

    return 0;
}
