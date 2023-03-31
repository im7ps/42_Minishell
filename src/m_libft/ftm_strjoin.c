/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftm_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:28:12 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:32:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ftm_strjoin(t_garbage **garbage, char const *s1, char const *s2, int flag)
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
		stack = gc_alloc(garbage, (sizeof(char) * (len1 + len2 + 1)), 1);
		if (!stack)
			return (NULL);
		while (*s1 != '\0')
			stack[i++] = *s1++;
	}
	while (*s2 != '\0')
		stack[i++] = *s2++;
	stack[i] = '\0';
	return (stack);
}
