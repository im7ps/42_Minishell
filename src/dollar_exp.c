/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/06 20:57:18 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t ft_smaller_string(char *str1, char *str2)
{
    if (ft_strlen(str1) > ft_strlen(str2))
        return (ft_strlen(str2));
    else
        return (ft_strlen(str1));
}

void    ft_expander_replace(char *str, t_minishell **minip)
{
    size_t      smaller;
    t_list      *mini;

    mini = (*minip)->envp_list;
    while (mini)
	{
        smaller = ft_smaller_string(str, mini->key);
		if (ft_strlen(str) == ft_strlen(mini->key))
        {
            if (!(ft_strncmp(str, mini->key, smaller)))
            {
                printf("Beccata!\n");
            }
        }
		mini = mini->next;
	}
}

char    *ft_expander_helper(t_minishell **minip, char *input)
{
    int     i;
    char    *tmp;
    t_minishell *mini;

    mini = *minip;
    i = 0;
    while (((input[i] > 64 && input[i] < 91) || input[i] == 95) && input[i] != '\0')
    {
        i++;
    }
    tmp = (char *) malloc (sizeof(char) * i + 1);
    ft_strlcpy(tmp, input, i + 1);
    ft_expander_replace(tmp, &mini);
    return (input);
}

/*  
*   ft_dollar_expander: 
*   se trovi il dollaro confronta con strncmp ogni key trovata nei nodi della lista envp, se trovi una corrispondenza prosegui
*   e modifica il campo input togliendo la key e inserendo al suo posto il value
*/
char	*ft_dollar_expander(t_minishell **minip)
{
	int	i;
    int len;
    t_minishell *mini;

    mini = *minip;
    len = ft_strlen(mini->input);
	i = -1;
	while (mini->input[++i])
	{
		if (mini->input[i] == '$')
		{
			if (i + 1 < len)
            {
                i++;
                if (!((mini->input[i] > 64 && mini->input[i] < 91) || mini->input[i] == 95))
                    return (NULL);
                mini->input = ft_expander_helper(minip, mini->input + i);
            }
		}
	}
	return (mini->input);
}