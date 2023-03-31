/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:57:06 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 19:57:16 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_fmv(t_xfillmv *fmv)
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
