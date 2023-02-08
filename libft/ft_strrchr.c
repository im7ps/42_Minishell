/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:48:40 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//The C library function char *strrchr(const char *str, int c) searches for the last occurrence of the character c (an unsigned char) in the string pointed to, by the argument str.
//source: https://www.tutorialspoint.com/c_standard_library/c_function_strrchr.htm

#include "../inc/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	ch;
	int		len;

	ch = c;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (*(str + len) == ch)
		{
			return ((char *)(str + len));
		}
		len--;
	}
	return (NULL);
}
