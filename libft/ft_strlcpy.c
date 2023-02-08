/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:58:48 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//strlcpy takes the destination's size as a parameter and will not write more than that many bytes, to prevent buffer overflow
//always writes a single NUL byte to the destination (if size is not zero). The resulting string is guaranteed to be NUL-terminated even if truncated
//source: https://en.wikibooks.org/wiki/C_Programming/C_Reference/nonstandard/strlcpy#:~:text=In%20computer%20programming%2C%20the%20strlcpy,cannot%20overflow%20the%20destination%20buffer.

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*src && i + 1 < dstsize)
	{
		*dst++ = *src++;
		i++;
	}
	if (i < dstsize)
		*dst = '\0';
	while (*src++)
		i++;
	return (i);
}
