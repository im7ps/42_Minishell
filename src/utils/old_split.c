/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:11:37 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 20:30:56 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**old_fill_m(t_minishell **minip, const char *s, t_xfillmv *fmv, char **matrix)
{
	t_xsubstr	sub;
	int			j;

	sub.i = 0;
	sub.len = 0;
	j = 0;
	while (j < fmv->num_w)
	{
		while (s[sub.i] == fmv->c)
				sub.i++;
		while (s[sub.i + sub.len] != fmv->c && s[sub.i + sub.len] != '\0')
			sub.len++;
		if (sub.len != 0)
		{
			matrix[j] = ft_substr_m(&(*minip)->garbage, s, sub);
			matrix[j][ft_strlen(matrix[j])] = '\0';
			j++;
		}
		sub.i += sub.len;
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
		if (*str != c && toggle == 0 && *str != '\0')
		{
			toggle = 1;
			num++;
		}
		else if (*str == c)
			toggle = 0;
		str++;
	}
	return (num);
}

char	**ft_old_split(t_minishell **minip, char const *s, char c)
{
	t_minishell	*mini;
	char		**matrix;
	int			str_len;
	t_xfillmv	*fmv;

	fmv = (t_xfillmv *) malloc (sizeof(t_xfillmv));
	ft_init_fmv(fmv);
	fmv->c = c;
	mini = *minip;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	fmv->num_w = old_count_w((char *)s, c);
	matrix = gc_alloc(&mini->garbage, (sizeof(char *) * (fmv->num_w + 1)), \
		fmv->num_w + 1);
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
