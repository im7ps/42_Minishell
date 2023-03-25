/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:52:29 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/25 14:35:00 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//inietta in una nuova strina allocata in memoria una parte di una precedente stringa
// il numero di char da copiare e' dato dall inizio (start) della stringa da cui partire
// e dal numero di caratteri (len) da iniettarci, finendo con un '\0'

#include "../inc/libft.h"
#include "../inc/minishell.h"
#include <stdio.h>

char	*ft_substr_m(t_garbage **garbage, char const *s, t_xsubstr sub)
{
	char	*stack;
	int		i;

	i = 0;
	sub.len--;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= (size_t)sub.i)
		sub.i = ft_strlen(s);
	if (ft_strlen(s) <= (size_t)sub.i + (size_t)sub.len)
	{
		sub.len = ft_strlen(s) - (size_t)sub.i;
	}
	stack = gc_alloc(garbage, (sizeof(char) * sub.len + 2), sub.len + 2);
	if (!stack)
		return (NULL);
	while (1 + sub.len--)										//MINISHELL: 1 + len-- (it was len--) per fargli includere la redirection nella stringa, che altrimenti verrebbe ignorata essendo il char separatore
		stack[i++] = s[sub.i++];								//MINISHELL: stack[i] = '\0'; era l originale, cambiato per mettere in pos stack[i] il reindirizzamento
	stack[i] = '\0';
	return (stack);
}
