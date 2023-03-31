/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:30:31 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:52:57 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*string;
	char	ch;

	ch = (char) c;
	string = (char *) s;
	while (string != NULL && n--)
	{
		if (*string == ch)
			return (string);
		else
			string++;
	}
	return (NULL);
}
