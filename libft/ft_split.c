/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:34:30 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//questa funzione e' complicata da immaginare per capirne il ragionamento, usa un debugger e fai test!

#include "../inc/libft.h"

char	**fill_m(const char *s, char c, char	**matrix, int num_w)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (j < num_w)									//il numero di volte che la stringa deve essere splittata
	{
		while (s[i] == c)								//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				i++;
		while (s[i + len] != c && s[i + len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
			len++;
		if (len != 0)									//se hai 0 char che ti indicano il punto di troncamento vuol dire che non devi troncare mai la stringa, in caso contrario...
		{
			matrix[j] = ft_substr(s, i, len);			//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
			j++;
		}
		i += len;								//i + len e' il trick per evitare di ricominciare la ricerca ogni volta dall inizio della stringa anziche' ricominciare dal char dopo il troncamento
		len = 0;
	}
	return (matrix);
}

int	count_w(char *str, char c)
{
	int	num;
	int	toggle;

	num = 0;
	toggle = 0;
	while (*str)
	{
		if (*str != c && toggle == 0 && *str != '\0')	//se siamo in una parola (*str != c), non l abbiamo ancora contata nel numero delle parole (toggle == 0) e la stringa non e' finita (*str != '\0')
		{
			toggle = 1;									//se incontri altri caratteri sappi che sei ancora nella stringa, non splittare
			num++;
		}
		else if (*str == c)								//dopo che trovi la corrispondenza con il carattere esegui un troncamento (toggle == 0)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ft_split(char const *s, char c)
{
	int		num_w;
	char	**matrix;

	if (!s)
		return (NULL);
	num_w = count_w((char *)s, c);								//capisci in quanti "pezzi" verra' divisa la stringa originale
	matrix = (char **) malloc(sizeof(char *) * (num_w + 1));	//occhio alle parentesi...
	if (!matrix)
		return (NULL);
	matrix[num_w] = NULL;
	matrix = fill_m(s, c, matrix, num_w);
	return (matrix);
}
