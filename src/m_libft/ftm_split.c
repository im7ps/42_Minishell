/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftm_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:42:07 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/01 00:06:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ftm_fill_mv(t_garbage **g, t_xfillmv *fmv, const char *s, char **mat)
{
	t_xsubstr	sub;

	while (fmv->j < fmv->num_w)
	{
		while (s[fmv->i] == fmv->c)
				fmv->i++;
		while (s[fmv->i + fmv->len] != '\0')
		{
			if (s[fmv->i + fmv->len] == 34 || s[fmv->i + fmv->len] == 39)
				fmv->qcount += ft_update_quotes(s[fmv->i + fmv->len]);
			if ((s[fmv->i + fmv->len] == fmv->c) && fmv->qcount == 0)
				break ;
			fmv->len++;
		}	
		if (fmv->len != 0)
		{
			sub.i = fmv->i;
			sub.len = fmv->len;
			mat[fmv->j] = ft_substr_m(g, s, sub);
			fmv->j++;
		}
		fmv->i += fmv->len;
		fmv->len = 0;
	}
	return (mat);
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
		if (*str != c && toggle == 0 && *str != '\0')
		{
			toggle = 1;
			num++;
		}
		else if (*str == c && qcount == 0)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ftm_split(t_garbage **garbage, char const *s, char c)
{
	char		**matrix;
	t_xfillmv	*fmv;

	fmv = gc_alloc(garbage, sizeof(t_xfillmv), 0);
	ft_init_fmv(fmv);
	fmv->c = c;
	if (!s)
		return (NULL);
	fmv->num_w = ftm_count_w((char *)s, c);
	matrix = gc_alloc(garbage, (sizeof(char *) * (fmv->num_w + 1)), \
		fmv->num_w + 1);
	if (!matrix)
		return (NULL);
	matrix[fmv->num_w] = NULL;
	matrix = ftm_fill_mv(garbage, fmv, s, matrix);
	return (matrix);
}
