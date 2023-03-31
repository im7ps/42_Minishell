/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:34:30 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:48:06 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"

char	**fill_m(const char *s, char c, char	**matrix, int num_w)
{
	int	i;
	int	j;
	int	len;
	int	quotes;
	int	qcount;

	i = 0;
	j = 0;
	len = 0;
	quotes = 0;
	qcount = 0;
	while (j < num_w)
	{
		while (s[i] == c)
				i++;
		while (s[i + len] != '\0')
		{
			if (s[i + len] == 34 || s[i + len] == 39)
			{
				quotes = ft_is_escaped(s[i + len], 0);
				if (quotes > 0)
					qcount++;
				else if (quotes < 0)
					qcount--;
			}
			if ((s[i + len] == c) && qcount == 0)
			{
				break ;
			}
			len++;
		}	
		if (len != 0)
		{
			matrix[j] = ft_substr(s, i, len);
			j++;
		}
		i += len;
		len = 0;
	}
	return (matrix);
}

int	count_w(char *str, char c)
{
	int	num;
	int	toggle;
	int	quotes;
	int	qcount;

	num = 0;
	toggle = 0;
	quotes = 0;
	qcount = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			quotes = ft_is_escaped(*str, 0);
			if (quotes > 0)
				qcount++;
			else if (quotes < 0)
				qcount--;
		}
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

char	**ft_split(char const *s, char c)
{
	int		num_w;
	char	**matrix;

	if (!s)
		return (NULL);
	num_w = count_w((char *)s, c);
	matrix = (char **) malloc(sizeof(char *) * (num_w + 1));
	if (!matrix)
		return (NULL);
	matrix[num_w] = NULL;
	matrix = fill_m(s, c, matrix, num_w);
	return (matrix);
}
