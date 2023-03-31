/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:29:49 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:46:11 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*stack;

	if (s1 == NULL)
		return (NULL);
	stack = (char *) malloc(sizeof(char) * (n + 1));
	if (s1 == NULL)
		return (NULL);
	else
		ft_memcpy(stack, s1, n);
	return (stack);
}
