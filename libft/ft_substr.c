/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:52:29 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/01 19:00:58 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//inietta in una nuova strina allocata in memoria una parte di una precedente stringa
// il numero di char da copiare e' dato dall inizio (start) della stringa da cui partire
// e dal numero di caratteri (len) da iniettarci, finendo con un '\0'

#include "../inc/libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*stack;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		start = ft_strlen(s);
	if (ft_strlen(s) <= start + len)
	{
		len = ft_strlen(s) - start;
	}
	stack = (char *) malloc (sizeof(char) * len + 2);		//MINISHELL: +2 per contenere EOF e char reindirizzamento (| < > << >>)
	if (!stack)
		return (NULL);
	while (1 + len--)										//MINISHELL: 1 + len-- (it was len--) per fargli includere la redirection nella stringa, che altrimenti verrebbe ignorata essendo il char separatore
		stack[i++] = s[start++];								//MINISHELL: stack[i] = '\0'; era l originale, cambiato per mettere in pos stack[i] il reindirizzamento
	stack[i] = '\0';
	return (stack);
}
