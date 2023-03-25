/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftm_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:14:31 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/25 14:35:42 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ftm_itoa(t_garbage **garbage, int n)
{
	char	*digits;
	int		len;
	char	*str_num;

	digits = "0123456789";									//un array di cifre, ci faranno comodo dopo
	len = numlen(n);										//calcola da quante caselle andra' creato l-array dove riscriveremo il numero in stringa
	//str_num = (char *) malloc(sizeof(char) * (len + 1));
	str_num = gc_alloc(garbage, (sizeof(char) * (len + 1)), len + 1);
	if (str_num == NULL)
		return (NULL);
	str_num[len] = '\0';									//questo e' il motivo del (+ 1) nella malloc, serve lo spazio per mettere il char che comunica che la stringa e' terminata
	if (n < 0)
	{
		str_num[0] = '-';									//se e' negativo il primo elemento dell array e' ovviamente un meno
		if (n == -2147483648)								//n == -2147483648 e' un caso particolare, il suo corrispettivo positivo non puo' essere gestito perche' e' letteralmente troppo grande
		{
			str_num[1] = '2';								//mettiamo "a mano" il 2 come secondo elemento dell array e ADESSO possiamo lavorare con i positivi
			n = 147483648;
		}
		else												//se il numero invece non e' un caso particolare banalmente lo moltiplichiamo per -1 e abbiamo il suo positivo
			n *= -1;
	}
	return (converter(str_num, digits, len, n));
}