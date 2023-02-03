/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:00 by sgerace           #+#    #+#             */
/*   Updated: 2022/05/24 17:04:13 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_address(unsigned long address, char *hex_vocabulary)
{
	int		i;

	i = 0;
	if (address >= 16)
		i += ft_print_address((address / 16), hex_vocabulary);
	i += ft_putchar(hex_vocabulary[(address % 16)]);
	return (i);
}

int	ft_print_ptr(unsigned long address, char *hex_vocabulary)
{
	int		i;

	i = 2;
	ft_putchar('0');
	ft_putchar('x');
	i += ft_print_address(address, hex_vocabulary);
	return (i);
}

int	ft_print_int(int number)
{
	int	i;

	i = 0;
	if (number == -2147483648)
	{
		i += ft_putchar('-');
		i += ft_putchar('2');
		number = 147483648;
	}
	if (number < 0)
	{
		i += ft_putchar('-');
		number *= -1;
	}
	if (number >= 10)
	{
		i += ft_print_int(number / 10);
		i += ft_print_int(number % 10);
	}
	else
	{
		i += ft_putchar(48 + number);
	}
	return (i);
}

int	ft_print_u_int(unsigned int number)
{
	int	i;

	i = 0;
	if (number >= 10)
	{
		i += ft_print_int(number / 10);
		i += ft_print_int(number % 10);
	}
	else
	{
		i += ft_putchar(48 + number);
	}
	return (i);
}

int	ft_print_num_hex(unsigned int hex_number, char *hex_vocabulary)
{
	int		i;

	i = 0;
	if (hex_number >= 16)
		i += ft_print_num_hex((hex_number / 16), hex_vocabulary);
	i += ft_putchar(hex_vocabulary[(hex_number % 16)]);
	return (i);
}
