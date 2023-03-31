/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:57:47 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:46:36 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	ch;
	size_t	i;

	ch = *needle;
	i = ft_strlen(needle);
	if (ch == '\0')
		return ((char *) haystack);
	while (*haystack != '\0' && len-- >= i)
	{
		if ((ch == *haystack) && (ft_memcmp(haystack, needle, i) == 0))
			return ((char *) haystack);
		haystack++;
	}
	return (NULL);
}
