/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:34:30 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/24 23:43:57 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//questa funzione e' complicata da immaginare per capirne il ragionamento, usa un debugger e fai test!

#include "../inc/libft.h"
#include "../inc/minishell.h"

char	**fill_m(const char *s, char c, char	**matrix, int num_w)
{
	int	i;
	int	j;
	int	len;
	int	quotes;
	int	qcount;

	i = 0;
	j = 0;
	len = 0;
	quotes = 0;
	qcount = 0;
	while (j < num_w)									//il numero di volte che la stringa deve essere splittata
	{
		while (s[i] == c)								//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				i++;
		while (s[i + len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
		{
			if (s[i + len] == 34 || s[i + len] == 39)
			{
				quotes = ft_is_escaped(s[i + len], 0);
				if (quotes > 0)
					qcount++;
				else if (quotes < 0)
					qcount--;
			}
			if ((s[i + len] == c) && qcount == 0)
			{
				break ;
			}
			len++;
		}	
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
	int	quotes;
	int	qcount;

	num = 0;
	toggle = 0;
	quotes = 0;
	qcount = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			quotes = ft_is_escaped(*str, 0);
			if (quotes > 0)
				qcount++;
			else if (quotes < 0)
				qcount--;
		}
		if (*str != c && toggle == 0 && *str != '\0')	//se siamo in una parola (*str != c), non l abbiamo ancora contata nel numero delle parole (toggle == 0) e la stringa non e' finita (*str != '\0')
		{
			toggle = 1;									//se incontri altri caratteri sappi che sei ancora nella stringa, non splittare
			num++;
		}
		else if (*str == c && qcount == 0)								//dopo che trovi la corrispondenza con il carattere esegui un troncamento (toggle == 0)
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
	num_w = count_w((char *)s, c);
	matrix = (char **) malloc(sizeof(char *) * (num_w + 1));
	if (!matrix)
		return (NULL);
	matrix[num_w] = NULL;
	matrix = fill_m(s, c, matrix, num_w);
	//int i = 0;
	// while (matrix[i])
	// 	ft_printf("%s\n", matrix[i++]);
	return (matrix);
}
