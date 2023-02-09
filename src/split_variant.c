/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:01:20 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/09 19:18:37 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_escaped(char	c)
{
	static	bool	d_quote;
	static	bool	s_quote;

	if (c == 34 && !(d_quote || s_quote))
	{
		d_quote = true;
		// ft_printf("dquotes activated\n");
		return (1);
	}
	else if (c == 39 && !(d_quote || s_quote))
	{
		s_quote = true;
		// ft_printf("squotes activated\n");
		return (2);
	}
	else if (c == 34 && d_quote)
	{
		d_quote = false;
		// ft_printf("dquotes disabled\n");
		return (-1);
	}
	else if (c == 39 && s_quote)
	{
		s_quote = false;
		// ft_printf("squotes disabled\n");
		return (-2);
	}
	return (0);
}

char	**fill_mv(const char *s, char *c, char	**matrix, int num_w)
{
	int	i;
	int	j;
	int	len;
	int	quotes;

	i = 0;
	j = 0;
	len = 0;
	quotes = 0;
	while (j < num_w)									//il numero di volte che la stringa deve essere splittata
	{
		while ((s[i] == c[0] || s[i] == c[1] || s[i] == c[2]))		//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				i++;
		while (s[i + len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
		{			
			if (s[i + len] == 34 || s[i + len] == 39)
			{
				quotes = ft_is_escaped(s[i + len]);
			}
			if ((s[i + len] == c[0] || s[i + len] == c[1] || s[i + len] == c[2]) && quotes <= 0)
				break ;
			len++;
		}
		if (len != 0)									//se hai 0 char che ti indicano il punto di troncamento vuol dire che non devi troncare mai la stringa, in caso contrario...
		{
			if (j == 0)
			{
				matrix[j] = ft_substr(s, i, len);			//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
				matrix[j][i + len] = s[i + len];
			}
			else
			{
				matrix[j] = ft_substr(s, i + 1, len);			//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
				matrix[j][i + len] = s[i + len];
			}
			j++;
		}
		i += len;								//i + len e' il trick per evitare di ricominciare la ricerca ogni volta dall inizio della stringa anziche' ricominciare dal char dopo il troncamento
		len = 0;
	}
	return (matrix);
}

int	count_wv(char *str, char *c)
{
	int	num;
	int	toggle;
	int	quotes;

	num = 0;
	toggle = 0;
	quotes = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			quotes = ft_is_escaped(*str);
		}
		if ((*str != c[0] || *str != c[1] || *str != c[2]) \
			&& toggle == 0 && *str != '\0')								//se siamo in una parola (*str != c), non l abbiamo ancora contata nel numero delle parole (toggle == 0) e la stringa non e' finita (*str != '\0')
		{
			toggle = 1;													//se incontri altri caratteri sappi che sei ancora nella stringa, non splittare
			num++;
		}
		else if ((*str == c[0] || *str == c[1] || *str == c[2]) && quotes <= 0)			//dopo che trovi la corrispondenza con il carattere esegui un troncamento (toggle == 0)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ft_split_variant(char *s)
{
	int		num_w;
	char	**matrix;
	char	c[3];

	c[0] = '|';
	c[1] = '>';
	c[2] = '<';
	if (!s)
		return (NULL);
	num_w = count_wv((char *)s, c);							//capisci in quanti "pezzi" verra' divisa la stringa originale
	matrix = (char **) malloc(sizeof(char *) * (num_w + 1));	//occhio alle parentesi...
	if (!matrix)
		return (NULL);
	matrix[num_w] = NULL;
	matrix = fill_mv(s, c, matrix, num_w);
	return (matrix);
}