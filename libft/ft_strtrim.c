/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:31:31 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:46:28 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	len = 0;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, *(s1 + len)))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
