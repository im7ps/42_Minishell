/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:54:00 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:10 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putchar(const char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *string)
{
	int	i;

	i = 0;
	if (!string)
		string = "(null)";
	while (string[i] != '\0')
	{
		write(1, &string[i], 1);
		i++;
	}
	return (i);
}
