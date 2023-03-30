/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:01:20 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/30 18:25:34 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_init_fmv(t_xfillmv *fmv)
{
	fmv->i = 0;
	fmv->j = 0;
	fmv->len = 0;
	fmv->qcount = 0;
	fmv->quotes = 0;
	fmv->num_w = 0;
	fmv->c = 0;
}

int	ft_get_word_length(const char *s, t_xfillmv *fmv)
{
	int	len;

	len = 0;
	while (s[fmv->i + len] != '\0')
	{
		if (s[fmv->i + len] == 34 || s[fmv->i + len] == 39)
		{
			fmv->quotes = ft_is_escaped(s[fmv->i + len], 0);
			if (fmv->quotes > 0)
				fmv->qcount++;
			else if (fmv->quotes < 0)
				fmv->qcount--;
		}
		if (ft_char_red(s[fmv->i + len]) && fmv->qcount == 0)
		{
			if (ft_char_red(s[fmv->i + len + 1]))
				len++;
			break ;
		}
		len++;
	}
	return (len + 1);
}

char	**fill_mv(t_minishell *mini, t_xfillmv *fmv, const char *s, char **matrix)
{
	t_xsubstr sub;

	while (fmv->j < fmv->num_w)									//il numero di volte che la stringa deve essere splittata
	{
		while (ft_char_red(s[fmv->i]))		//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
				fmv->i++;
		fmv->len = ft_get_word_length(s, fmv);
		if (fmv->len != 0)
		{
			while (s[fmv->i] == ' ')
			{
				s++;
				fmv->len--;
			}
			sub.i = fmv->i;
			sub.len = fmv->len;
			matrix[fmv->j] = ft_substr_m(&mini->garbage, s, sub);
			fmv->j++;
		}
		fmv->i += fmv->len;
		fmv->len = 0;
	}
	return (matrix);
}

int	ft_update_quotes(char c)
{
	int quotes;

	quotes = ft_is_escaped(c, 0);
	if (quotes > 0)
		return (1);
	else if (quotes < 0)
		return (-1);
	return (0);
}

int	count_wv(char *str, char *c, int toggle, int num)
{
	int	qcount;

	qcount = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
			qcount += ft_update_quotes(*str);
		if ((*str != c[0] || *str != c[1] || *str != c[2]) \
			&& toggle == 0 && *str != '\0')								//se siamo in una parola (*str != c), non l abbiamo ancora contata nel numero delle parole (toggle == 0) e la stringa non e' finita (*str != '\0')
		{
			toggle = 1;													//se incontri altri caratteri sappi che sei ancora nella stringa, non splittare
			num++;
		}
		else if ((*str == c[0] || *str == c[1] || *str == c[2]) && qcount == 0)			//dopo che trovi la corrispondenza con il carattere esegui un troncamento (toggle == 0)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ft_split_variant(t_minishell *mini, char *s)
{
	char	**matrix;
	char	c[3];
	t_xfillmv *fmv;

	fmv = gc_alloc(&mini->garbage, sizeof(t_xfillmv), 0);
	ft_init_fmv(fmv);
	c[0] = '|';
	c[1] = '>';
	c[2] = '<';
	if (!s)
		return (NULL);
	fmv->num_w = count_wv((char *)s, c, 0, 0);							//capisci in quanti "pezzi" verra' divisa la stringa originalej
	matrix = gc_alloc(&mini->garbage, (sizeof(char *) * (fmv->num_w + 1)), fmv->num_w + 1);
	if (!matrix)
		return (NULL);
	matrix[fmv->num_w] = NULL;
	matrix = fill_mv(mini, fmv, s, matrix);
	return (matrix);
}

















// char	**old_fill_m(t_minishell **minip, const char *s, char c, char	**matrix, int num_w)
// {
// 	t_xsubstr sub;
// 	int	j;
// 	int	len;

// 	sub.i = 0;
// 	sub.len = 0;
// 	j = 0;
// 	while (j < num_w)									//il numero di volte che la stringa deve essere splittata
// 	{
// 		while (s[sub.i] == c)								//l inizio della stringa potrebbe essere piena di caratteri che ti indicano che devi splittare...ma sei all'inizio della stringa, ignorali!
// 				sub.i++;
// 		while (s[sub.i + sub.len] != c && s[sub.i + sub.len] != '\0')	//conta da quanti char e' composta la stringa da iniettare, info sul motivo di (i + len) in basso
// 			sub.len++;
// 		if (sub.len != 0)									//se hai 0 char che ti indicano il punto di troncamento vuol dire che non devi troncare mai la stringa, in caso contrario...
// 		{
// 			matrix[j] = ft_substr_m(&(*minip)->garbage, s, sub);		//...usa substring per iniettare la stringa dentro la riga j-esima della matrice
// 			matrix[j][ft_strlen(matrix[j])] = '\0';
// 			j++;
// 		}
// 		sub.i += sub.len;										//i + len e' il trick per evitare di ricominciare la ricerca ogni volta dall inizio della stringa anziche' ricominciare dal char dopo il troncamento
// 		sub.len = 0;
// 	}
// 	return (matrix);
// }

// int	old_count_w(char *str, char c)
// {
// 	int	num;
// 	int	toggle;

// 	num = 0;
// 	toggle = 0;
// 	while (*str)
// 	{
// 		if (*str != c && toggle == 0 && *str != '\0')	//se siamo in una parola (*str != c), non l abbiamo ancora contata nel numero delle parole (toggle == 0) e la stringa non e' finita (*str != '\0')
// 		{
// 			toggle = 1;									//se incontri altri caratteri sappi che sei ancora nella stringa, non splittare
// 			num++;
// 		}
// 		else if (*str == c)								//dopo che trovi la corrispondenza con il carattere esegui un troncamento (toggle == 0)
// 			toggle = 0;
// 		str++;
// 	}
// 	return (num);
// }

// char	**ft_old_split(t_minishell **minip, char const *s, char c)
// {
// 	t_minishell *mini;
// 	char		**matrix;
// 	int			num_w;
// 	int			str_len;

// 	mini = *minip;
// 	if (!s)
// 		return (NULL);
// 	str_len = ft_strlen(s);
// 	num_w = old_count_w((char *)s, c);
// 	matrix = gc_alloc(&mini->garbage, (sizeof(char *) * (num_w + 1)), num_w + 1);
// 	if (!matrix)
// 		return (NULL);
// 	matrix[num_w] = NULL;
// 	matrix = old_fill_m(minip, s, c, matrix, num_w);
// 	return (matrix);
// }




















































