/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:05:39 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:50:36 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*stack;

	stack = (char *) malloc(sizeof(char) * size);
	if (!stack)
		return (0);
	else
		ft_bzero(stack, count);
	return (stack);
}
