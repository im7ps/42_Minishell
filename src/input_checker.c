/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:47:30 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/16 21:01:29 by sgerace          ###   ########.fr       */
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

int	ft_double_red_checker(char	*input)
{
	int	redcount;
	int	quotescount;
	int	quotestoggle;
	int	i;
	
	i = 0;
	redcount = 0;
	quotescount = 0;
	quotestoggle = 0;
	while (input[i])
	{
		quotescount = ft_is_escaped(input[i]);
		if (quotescount > 0)
			quotestoggle++;
		else if (quotescount < 0)
			quotestoggle--;
		if (quotestoggle == 0)
		{
			if (redcount == 0)
			{
				if (input[i] == '|')
				{
					redcount = -1;
				}
				else if (input[i] == '<')
				{
					if (input[i + 1] == '<')
						i++;
					redcount = -2;
				}
				else if (input[i] == '>')
				{
					if (input[i + 1] == '>')
						i++;
					redcount = -2;
				}
			}
			else if (redcount == -1)
			{
				if ((input[i] != '|' && input[i] != ' '))
				{
					redcount = 0;
				}
				if (input[i] == '|')
				{
					ft_printf("Doppia pipe!\n");
					return (-1);
				}
			}
			else if (redcount == -2)
			{
				if ((input[i] != '|' && input[i] != '>' && input[i] != '<' && input[i] != ' '))
				{
					redcount = 0;
				}
				else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
				{
					ft_printf("Doppia pipe\n");
					return (-1);
				}
			}
		}
		i++;
	}
	return (0);
}

/*controlla che ci siano solo caratteri autorizzati: ", ', >, <, $,  , |, -, numeri, lettere*/
int	ft_input_checker(char	*input)
{
	int	i;
	int	quotes;
	int	qcount;

	i = 0;
	quotes = 0;
	qcount = 0;
	while (input[i])
	{
		// if (!(input[i] == ';' || input[i] == '/' || input[i] == '.' || input[i] == '=' || input[i] == '"' || input[i] == '$' || input[i] == '\'' || input[i] == '|' || input[i] == '-' || \
		// 	input[i] == '>' || input[i] == '<' || input[i] == ' ' || (input[i] > 47 && input[i] < 58) || \
		// 	input[i] == '_' || (input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)))
		// {
		// 	return (1);
		// }
		quotes = ft_is_escaped(input[i]);
		if(quotes > 0)
			 qcount++;
		else if (quotes < 0)
			qcount--;
		i++;
	}
	if (input[i - 1] == '>' || input[i - 1] == '|' || input[i - 1] == '<')
		return(1);
	if (ft_double_red_checker(input))
		return (1);
	return (qcount);
}