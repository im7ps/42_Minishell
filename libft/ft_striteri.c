/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:21:07 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 20:14:32 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);		//gli passiamo l indirizzo per lavorare sulla vera stringa, non una copia! (in realta' il prototipo accetta un puntatore, s[i] sarebbe "solo" un valore)
		i++;
	}
}
