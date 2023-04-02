/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:47:30 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 13:13:14 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_double_red_checker(char *input, bool redtoggle)
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
		else if (!ft_char_red(input[i]) && !(input[i] == ' ' \
			|| input[i] == '\t'))
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

int	ft_input_checker(char	*input, bool onlytab)
{
	int	res;

	if (ft_is_onlytab(input, onlytab))
	{
		return (0);
	}
	res = ft_quotes_checker(input, 0, 0);
	if (res != 0)
	{
		ft_printf("Input error\n");
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>' || \
		input[ft_strlen(input) - 1] == '|' || \
		input[ft_strlen(input) - 1] == '<')
	{
		ft_printf("Input error\n");
		return (1);
	}
	if (ft_double_red_checker(input, false))
	{
		ft_printf("Input error\n");
		return (1);
	}
	return (res);
}
