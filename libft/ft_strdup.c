/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:40:54 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/03 18:22:23 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	dim;
	char	*stack;

	if (s1 == NULL)
		return (NULL);
	dim = ft_strlen(s1) + 1;
	stack = (char *) malloc(sizeof(char) * dim);
	if (s1 == NULL)
		return (NULL);
	else
		ft_memcpy(stack, s1, dim);
	return (stack);
}
