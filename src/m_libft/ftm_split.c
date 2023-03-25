/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftm_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:42:07 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/25 14:35:57 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ftm_fill_mv(t_garbage **garbage, t_xfillmv *fmv, const char *s, char **matrix)
{
	t_xsubstr sub;

	while (fmv->j < fmv->num_w)								//il numero di volte che la stringa deve essere splittata
	{
		while (s[fmv->i] == fmv->c)								//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				fmv->i++;
		while (s[fmv->i + fmv->len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
		{
			if (s[fmv->i + fmv->len] == 34 || s[fmv->i + fmv->len] == 39)
				fmv->qcount += ft_update_quotes(s[fmv->i + fmv->len]);
			if ((s[fmv->i + fmv->len] == fmv->c) && fmv->qcount == 0)
				break ;
			fmv->len++;
		}	
		if (fmv->len != 0)									//se hai 0 char che ti indicano il punto di troncamento vuol dire che non devi troncare mai la stringa, in caso contrario...
		{
			sub.i = fmv->i;
			sub.len = fmv->len;
			matrix[fmv->j] = ft_substr_m(garbage, s, sub);		//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
			fmv->j++;
		}
		fmv->i += fmv->len;								//i + len e' il trick per evitare di ricominciare la ricerca ogni volta dall inizio della stringa anziche' ricominciare dal char dopo il troncamento
		fmv->len = 0;
	}
	return (matrix);
}

int	ftm_count_w(char *str, char c)
{
	int	num;
	int	toggle;
	int	qcount;

	num = 0;
	toggle = 0;
	qcount = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
			qcount += ft_update_quotes(*str);
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

char	**ftm_split(t_garbage **garbage, char const *s, char c)
{
	char	**matrix;
	t_xfillmv *fmv;

	fmv = gc_alloc(garbage, sizeof(t_xfillmv), 0);
	ft_init_fmv(fmv);
	fmv->c = c;
	if (!s)
		return (NULL);
	fmv->num_w = ftm_count_w((char *)s, c);
	matrix = gc_alloc(garbage, (sizeof(char *) * (fmv->num_w + 1)), fmv->num_w + 1);
	if (!matrix)
		return (NULL);
	matrix[fmv->num_w] = NULL;
	matrix = ftm_fill_mv(garbage, fmv, s, matrix);
	return (matrix);
}
