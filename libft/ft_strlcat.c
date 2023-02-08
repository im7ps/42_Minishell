/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:23:33 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The strlcat() function (with the L) appends one string onto the end of the other.
// Characters from string src are appended to string dst.
// !!The dstsize argument is equal to the size of the dst buffer, which caps the number of characters copied to this size, minus one for the null character!!
// The strlcat() function returns the combined length of both src and dst strings (not counting their terminating null characters). This result is used to determine whether the final string was truncated.
// source: https://c-for-dummies.com/blog/?p=3896

#include "../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (dest_len >= dstsize || dstsize == 0)
		return (src_len + dstsize);
	while (src[i] != '\0' && (dest_len + i + 1) < dstsize)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
