/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:04:53 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/16 21:25:56 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//str = strjoin(C) constructs str by linking the elements of C with a space between consecutive elements.
// C can be a cell array of character vectors or a string array.
// source: https://fr.mathworks.com/help/matlab/ref/strjoin.html#:~:text=str%20%3D%20strjoin(%20C%20)%20constructs,with%20the%20elements%20in%20delimiter%20.

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int flag)
{
	size_t		len1;
	size_t		len2;
	size_t		i;
	char		*stack;

	if (flag == 1)
	{
		if (!s2)
			return (NULL);
		return ((char *)s2);
	}
	if (flag == 2)
	{
		if (!s1)
			return (NULL);
		return ((char *)s1);
	}
	else
	{
		if (!s1 || !s2)
			return (NULL);
		i = 0;
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		stack = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
		if (!stack)
			return (NULL);
		while (*s1 != '\0')
			stack[i++] = *s1++;
	}
	while (*s2 != '\0')
		stack[i++] = *s2++;
	stack[i] = '\0';			// il null character va messo solo alla fine, fra una stringa e l'altra non ci va
	return (stack);
}
