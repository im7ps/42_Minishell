/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:11:54 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// A volte, la memoria dinamica dovrebbe essere sovrascritta con zeri per cancellarla dai valori di spazzatura
// Richiede due argomenti, l’indirizzo iniziale della regione di memoria e il numero di byte che devono essere azzerati.
//fonte: https://www.delftstack.com/it/howto/c/bzero-in-c/

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = s;	//lo facciamo perche s è settato a void ma noi dobbiamo lavorare su una stringa!
	while (n--)
	{
		*str++ = '\0';
	}
}
