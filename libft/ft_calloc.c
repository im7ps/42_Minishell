/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:05:39 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 18:34:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The C library function void *calloc(size_t nitems, size_t size) allocates the requested memory and returns a pointer to it.
// The difference in malloc and calloc is that malloc does not set the memory to zero where as calloc sets allocated memory to zero
// fonte: https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm

void	*ft_calloc(size_t count, size_t size)
{
	void	*stack;
	size_t	dimension;

	dimension = count * size;
	stack = (char *) malloc(sizeof(char) * dimension);
	if (!stack)											//se l-allocazione fallisce return 0
		return (0);
	else
		ft_bzero(stack, dimension);						//else allochiamo un-area di memoria inizializzata da vari '\0'
	return (stack);
}
