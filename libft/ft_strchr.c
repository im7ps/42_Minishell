/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:21:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The C library function strchr searches for the first occurrence of the character c in the string pointed to by the argument str
// This returns a pointer to the first occurrence of the character c in the string str, or NULL if the character is not found.
// source: https://www.tutorialspoint.com/c_standard_library/c_function_strchr.htm

#include "../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *) s);
		s++;
	}
	if (*s == ch)					//ultimo controllo, uno user simpaticone potrebbe passare proprio '\0' come char da cercare! (0 nel decimal set degli ascii)
		return ((char *)s);
	return (NULL);
}
