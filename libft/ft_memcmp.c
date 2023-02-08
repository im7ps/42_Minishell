/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:44:49 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Confronta i primi n caratteri di s1 e s2 e restituisce un valore che ne indica la relazione.
// Il segno di un valore restituito diverso da zero è il segno della differenza tra la prima coppia di valori diversi nei buffer.
// I valori vengono interpretati come unsigned char
// source: https://docs.microsoft.com/it-it/cpp/c-runtime-library/reference/memcmp-wmemcmp?view=msvc-170

#include "../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*str1;
	unsigned const char	*str2;

	i = 0;
	str1 = s1;
	str2 = s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);			//basta ritornare la sottrazione e funziona in ogni caso perche' questi valori sono unsigned! (positivi o uguali a zero ma mai negativi)
	i++;
	}
	return (0);
}
