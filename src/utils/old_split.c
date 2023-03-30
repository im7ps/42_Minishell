/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:11:37 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/30 18:58:22 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**old_fill_m(t_minishell **minip, const char *s, t_xfillmv *fmv, char **matrix)
{
	t_xsubstr sub;
	int	j;
	int	len;

	sub.i = 0;
	sub.len = 0;
	j = 0;
	while (j < fmv->num_w)									//il numero di volte che la stringa deve essere splittata
	{
		while (s[sub.i] == fmv->c)								//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				sub.i++;
		while (s[sub.i + sub.len] != fmv->c && s[sub.i + sub.len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
			sub.len++;
		if (sub.len != 0)									//se hai 0 char che ti indicano il punto di troncamento vuol dire che non devi troncare mai la stringa, in caso contrario...
		{
			matrix[j] = ft_substr_m(&(*minip)->garbage, s, sub);		//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
			matrix[j][ft_strlen(matrix[j])] = '\0';
			j++;
		}
		sub.i += sub.len;										//i + len e' il trick per evitare di ricominciare la ricerca ogni volta dall inizio della stringa anziche' ricominciare dal char dopo il troncamento
		sub.len = 0;
	}
	return (matrix);
}

int	old_count_w(char *str, char c)
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

char	**ft_old_split(t_minishell **minip, char const *s, char c)
{
	t_minishell *mini;
	char		**matrix;
	int			str_len;
	t_xfillmv 	*fmv;

	fmv = (t_xfillmv*) malloc (sizeof(t_xfillmv));
	ft_init_fmv(fmv);
	fmv->c = c;
	mini = *minip;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	fmv->num_w = old_count_w((char *)s, c);
	matrix = gc_alloc(&mini->garbage, (sizeof(char *) * (fmv->num_w + 1)), fmv->num_w + 1);
	if (!matrix)
		return (NULL);
	matrix[fmv->num_w] = NULL;
	matrix = old_fill_m(minip, s, fmv, matrix);
	fmv->num_w = 0;
	fmv->c = 0;
	free(fmv);
	fmv = NULL;
	return (matrix);
}