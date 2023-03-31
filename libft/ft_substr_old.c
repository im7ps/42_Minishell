/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:58:47 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:45:45 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr_old(char const *s, unsigned int start, int len)
{
	char	*stack;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		start = ft_strlen(s);
	if (ft_strlen(s) <= start + len)
	{
		len = ft_strlen(s) - start;
	}
	stack = (char *) malloc (sizeof(char) * (len + 1));
	if (!stack)
		return (NULL);
	while (len--)
		stack[i++] = s[start++];
	stack[i] = '\0';
	return (stack);
}
