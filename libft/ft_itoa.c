/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:46:20 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//itoa () function in C language converts int data type to string data type. (da int numero a char *numero)
//fonte: https://fresh2refresh.com/c-programming/c-type-casting/c-itoa-function/

#include "../inc/libft.h"

int	numlen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)			//se non ti e' chiaro questo ciclo usa un compilatore e capirai
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*converter(char *str_num, char *digits, int len, int n)
{
	if (n == 0)
		str_num[--len] = '0';			//se il numero e' zero va prima aggiustato l indice (--len) e quindi al posto del "-" messo in riga 67 ci sara' lo zero, e poi return
	else
	{
		while (n > 0)
		{
			str_num[--len] = digits[n % 10]; //es: n = 481 -> 481 % 10 = 1, e l'1 e' proprio all indice 1 della stringa creata in riga 59, quindi funziona
			n /= 10;
		}
	}
	return (str_num);
}

char	*ft_itoa(int n)
{
	char	*digits;
	int		len;
	char	*str_num;

	digits = "0123456789";									//un array di cifre, ci faranno comodo dopo
	len = numlen(n);										//calcola da quante caselle andra' creato l-array dove riscriveremo il numero in stringa
	str_num = (char *) malloc(sizeof(char) * (len + 1));
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
