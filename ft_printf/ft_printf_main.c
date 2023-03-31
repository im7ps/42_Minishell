/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:13:42 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:51:41 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	printf_switch(va_list list, const char *string)
{
	int	i;

	i = 0;
	if (string[i] == 'c')
		i += ft_putchar(va_arg(list, int));
	else if (string[i] == 's')
		i += ft_putstr(va_arg(list, char *));
	else if (string[i] == 'p')
		i += ft_print_ptr(va_arg(list, unsigned long), "0123456789abcdef");
	else if (string[i] == 'd' || string[i] == 'i')
		i += ft_print_int(va_arg(list, int));
	else if (string[i] == 'u')
		i += ft_print_u_int(va_arg(list, unsigned int));
	else if (string[i] == 'x')
		i += ft_print_num_hex(va_arg(list, unsigned int), "0123456789abcdef");
	else if (string[i] == 'X')
		i += ft_print_num_hex(va_arg(list, unsigned int), "0123456789ABCDEF");
	else if (string[i] == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const	char *string, ...)
{
	va_list	list;
	int		i;
	int		len;

	va_start(list, string);
	i = 0;
	len = 0;
	while (string[i] != '\0' && string[i])
	{
		if (string[i] == '%')
		{
			i++;
			len += printf_switch(list, &string[i]);
		}
		else
			len += ft_putchar(string[i]);
		i++;
	}
	va_end(list);
	return (len);
}
