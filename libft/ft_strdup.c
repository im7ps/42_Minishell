/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:40:54 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:12:18 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"

char	*ft_strdup_m(t_garbage **garbage, const char *s1)
{
	size_t	dim;
	char	*stack;

	if (s1 == NULL)
		return (NULL);
	dim = ft_strlen(s1) + 1;
	stack = gc_alloc(garbage, (sizeof(char) * dim), dim);
	if (s1 == NULL)
		return (NULL);
	else
		ft_memcpy(stack, s1, dim);
	return (stack);
}
