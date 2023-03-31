/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:48:40 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:46:20 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	ch;
	int		len;

	ch = c;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (*(str + len) == ch)
		{
			return ((char *)(str + len));
		}
		len--;
	}
	return (NULL);
}
