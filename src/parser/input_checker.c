/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:47:30 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 13:28:31 by sgerace          ###   ########.fr       */
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

int	ft_is_escaped(char	c, int flag)
{
	static	bool	d_quote;
	static	bool	s_quote;

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

int	ft_double_red_checker(char *input, int redcount, bool redtoggle)
{
	int		i;

	i = 0;
    while (input[i])
    {
        if (ft_char_red(input[i]))
        {
			if (redtoggle == true)
				return (1);
            if ((input[i] == '<' && input[i] && input[i + 1] == '<') || \
                (input[i] == '>' && input[i] && input[i + 1] == '>'))
			{
                i++;
            }
			redtoggle = true;
        }
		else if (!ft_char_red(input[i]) && !(input[i] == ' ' || input[i] == '\t'))
		{
			redtoggle = false;
		}
        i++;
    }
    return (0);
}

int	ft_is_onlytab(char	*input, bool onlytab)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\'')
			onlytab = false;
		i++;
	}
	if (onlytab)
	{
		return (1);
	}
	return (0);
}

int	ft_quotes_checker(char	*input, int quotes, int qcount)
{
	int	i;

	i = 0;
	while (input[i])
	{
		quotes = ft_is_escaped(input[i], 0);
		if (quotes > 0)
			 qcount++;
		else if (quotes < 0)
			qcount--;
		i++;
	}
	return (qcount);
}

/*controlla che ci siano solo caratteri autorizzati: ", ', >, <, $,  , |, -, numeri, lettere*/
int	ft_input_checker(char	*input, int quotes, int qcount, bool onlytab)
{
	int	res;
	
	if (ft_is_onlytab(input, onlytab))
	{
		ft_printf("Coglione\n");
		return (1);
	}
	res = ft_quotes_checker(input, 0, 0);
	if (res != 0)
	{
		ft_printf("Quotes deesparee salveenee\n");
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>' || \
		input[ft_strlen(input) - 1] == '|' || \
		input[ft_strlen(input) - 1] == '<')
		{
			ft_printf("L ultimo char non può eser una rojadirecta\n");
			return (1);
		}
	if (ft_double_red_checker(input, 0, false))
	{
		ft_printf("Double rojadirection!\n");
		return (1);
	}
	return (res);
}