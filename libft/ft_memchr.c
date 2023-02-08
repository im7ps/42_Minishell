/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:30:31 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memchr searches for the first occurrence of the character c, analyzing n bytes
// source: https://www.tutorialspoint.com/c_standard_library/c_function_memchr.htm

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*string;
	char	ch;

	ch = (char) c;
	string = (char *) s;
	while (string != NULL && n--)
	{
		if (*string == ch)
			return (string); 		//returns a pointer to the matching byte
		else
			string++;
	}
	return (NULL);					//or NULL if the character does not occur in the given memory area
}
