/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:13:42 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:10 by sgerace          ###   ########.fr       */
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
	// va_end(list);
	return (len);
}

// int main(void)
// {
// 	char anything = '%';
// 	char *anything2 = "lunga6";
// 	int anything3 = 12;
// 	unsigned	int anything4 = 412324;
// 	unsigned	int anything5 = 1337;
// 	void *anything6 = &anything2;
// 	int	i = 0;
// 	int j = 0;

// 	i = printf("PRINTF: %c\n", anything);
// 	j = ft_printf("FT_PRINTF: %c\n", anything);
// 	printf("Numero di char letti con PRINTF: %i\n", i);
// 	printf("Numero di char letti con FT_PRINTF: %i\n", j);

// 	i = printf("PRINTF: %s\n", anything2);
// 	j = ft_printf("FT_PRINTF: %s\n", anything2);
// 	printf("Numero di char letti con PRINTF: %i\n", i);
// 	printf("Numero di char letti con FT_PRINTF: %i\n", j);

// 	i = printf("PRINTF: %d\n", anything3);
// 	j = ft_printf("FT_PRINTF: %d\n", anything3);
// 	printf("Numero di char letti con PRINTF: %i\n", i);
// 	printf("Numero di char letti con FT_PRINTF: %i\n", j);

// 	i = printf("PRINTF: %x\n", anything4);
// 	j = ft_printf("FT_PRINTF: %x\n", anything4);
// 	printf("Numero di char letti con PRINTF: %i\n", i);
// 	printf("Numero di char letti con FT_PRINTF: %i\n", j);

// 	i = printf("PRINTF: %X\n", anything5);
// 	j = ft_printf("FT_PRINTF: %X\n", anything5);
// 	printf("Numero di char letti con PRINTF: %i\n", i);
// 	printf("Numero di char letti con FT_PRINTF: %i\n", j);

// 	i = printf("PRINTF: %p\n", anything6);
// 	j = ft_printf("FT_PRINTF: %p\n", anything6);
// 	printf("Numero di char letti con PRINTF: %i\n", i);
// 	printf("Numero di char letti con FT_PRINTF: %i\n", j);
// 	return (0);
// }