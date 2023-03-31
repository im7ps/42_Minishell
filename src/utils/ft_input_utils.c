/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:45:21 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 19:45:31 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_reset_quotes(bool *d_quote, bool *s_quote)
{
	*d_quote = false;
	*s_quote = false;
}

int	ft_squote_x_norma(char c, bool *s_quote)
{
	if (c == 39 && s_quote)
	{
		*s_quote = false;
		return (-2);
	}
	return (0);
}

int	ft_is_escaped(char c, int flag)
{
	static bool	d_quote;
	static bool	s_quote;

	if (flag)
		ft_reset_quotes(&d_quote, &s_quote);
	if (c == 34 && !(d_quote || s_quote))
	{
		d_quote = true;
		return (1);
	}
	else if (c == 39 && !(d_quote || s_quote))
	{
		s_quote = true;
		return (2);
	}
	else if (c == 34 && d_quote)
	{
		d_quote = false;
		return (-1);
	}
	else if (c == 39 && s_quote)
		return (ft_squote_x_norma(c, &s_quote));
	return (0);
}

bool	ft_char_red(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
