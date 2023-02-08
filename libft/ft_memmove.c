/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:26:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//non consiglio di usare questo script, va facilmente in segmentation fault

#include "../inc/libft.h"

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
