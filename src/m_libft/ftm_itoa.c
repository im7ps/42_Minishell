/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftm_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:14:31 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:34:39 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ftm_itoa(t_garbage **garbage, int n)
{
	char	*digits;
	int		len;
	char	*str_num;

	digits = "0123456789";
	len = numlen(n);
	str_num = gc_alloc(garbage, (sizeof(char) * (len + 1)), len + 1);
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
