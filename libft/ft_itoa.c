/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:46:20 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:50:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	numlen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*converter(char *str_num, char *digits, int len, int n)
{
	if (n == 0)
		str_num[--len] = '0';
	else
	{
		while (n > 0)
		{
			str_num[--len] = digits[n % 10];
			n /= 10;
		}
	}
	return (str_num);
}

char	*ft_itoa(int n)
{
	char	*digits;
	int		len;
	char	*str_num;

	digits = "0123456789";
	len = numlen(n);
	str_num = (char *) malloc(sizeof(char) * (len + 1));
	if (str_num == NULL)
		return (NULL);
	str_num[len] = '\0';
	if (n < 0)
	{
		str_num[0] = '-';
		if (n == -2147483648)
		{
			str_num[1] = '2';
			n = 147483648;
		}
		else
			n *= -1;
	}
	return (converter(str_num, digits, len, n));
}
