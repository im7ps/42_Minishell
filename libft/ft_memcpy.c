/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:16:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memcpy copies n characters from memory area src to memory area dest.
// This function returns a pointer to destination
// source: https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm

#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*from;

	dest = dst;
	from = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		*dest++ = *from++;
	}
	return (dst);
}
