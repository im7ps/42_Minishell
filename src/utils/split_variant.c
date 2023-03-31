/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:01:20 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 19:57:58 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**fill_mv(t_minishell *mini, t_xfillmv *fmv, const char *s, char **m)
{
	t_xsubstr	sub;

	while (fmv->j < fmv->num_w)
	{
		while (ft_char_red(s[fmv->i]))
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
			m[fmv->j] = ft_substr_m(&mini->garbage, s, sub);
			fmv->j++;
		}
		fmv->i += fmv->len;
		fmv->len = 0;
	}
	return (m);
}

int	ft_update_quotes(char c)
{
	int	quotes;

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
			&& toggle == 0 && *str != '\0')
		{
			toggle = 1;
			num++;
		}
		else if ((*str == c[0] || *str == c[1] || *str == c[2]) && qcount == 0)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ft_split_variant(t_minishell *mini, char *s)
{
	char		**matrix;
	char		c[3];
	t_xfillmv	*fmv;

	fmv = gc_alloc(&mini->garbage, sizeof(t_xfillmv), 0);
	ft_init_fmv(fmv);
	c[0] = '|';
	c[1] = '>';
	c[2] = '<';
	if (!s)
		return (NULL);
	fmv->num_w = count_wv((char *)s, c, 0, 0);
	matrix = gc_alloc(&mini->garbage, (sizeof(char *) * (fmv->num_w + 1)), \
		fmv->num_w + 1);
	if (!matrix)
		return (NULL);
	matrix[fmv->num_w] = NULL;
	matrix = fill_mv(mini, fmv, s, matrix);
	return (matrix);
}
