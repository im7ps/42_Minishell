/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:26:56 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 19:49:10 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//non consiglio di usare questo script, va facilmente in segmentation fault

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*from;

	dest = dst;
	from = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dest < from)
		while (len--)
			*dest++ = *from++;
	else
	{
		from = from + (len - 1);
		dest += (len - 1);
		while (len--)
			*dest-- = *from--;
	}
	return (dst);
}
