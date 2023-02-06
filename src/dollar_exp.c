/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/06 17:12:11 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char    *ft_expander_helper(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        ft_printf("%c\n", input[i]);
        i++;
    }
    ft_printf("\n");
    return (input);
}

/*  
*   ft_dollar_expander: 
*   se trovi il dollaro confronta con strncmp ogni key trovata nei nodi della lista envp, se trovi una corrispondenza prosegui
*   e modifica il campo input togliendo la key e inserendo al suo posto il value
*/
char	*ft_dollar_expander(char *input)
{
	int	i;
    int len;

    len = ft_strlen(input);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
		{
			if (i + 1 < len)
            {
                i++;
                if (!((input[i] > 65 && input[i] < 90) || input[i] == 95))
                    return (1);
                input = ft_expander_helper(input + i);
            }
		}
	}
	return (input);
}