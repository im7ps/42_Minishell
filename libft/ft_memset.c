/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:17:46 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memset() is used to fill a block of memory with a particular value.
// source: https://www.geeksforgeeks.org/memset-c-example/

#include "../inc/libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	char	l;
	char	*k;

	k = str;
	l = c;
	while (len--)
	{
		*k++ = l;
	}
	return (str);
}
