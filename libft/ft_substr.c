/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:52:29 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 20:44:28 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//inietta in una nuova strina allocata in memoria una parte di una precedente stringa
// il numero di char da copiare e' dato dall inizio (start) della stringa da cui partire
// e dal numero di caratteri (len) da iniettarci, finendo con un '\0'

#include "libft.h"

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
