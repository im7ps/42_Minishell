/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:58:06 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 18:32:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atoi converte un numero scritto in stringa nel suo corrispettivo int

int	ft_atoi(const char *str)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' 	//salta qualsiasi spazio iniziale
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')							//controlla se c-e' un segno SUBITO DOPO gli spazi
 	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')						//es str = "125" passo1: -> res = (0 * 10) + (1) = 1
		result = (result * 10) + (str[i++] - '0');				//es passo2: -> res = (1 * 10) + (2) = 12
	return (result * sign);										//es passo3: -> res = (12 * 10) + (5) = 125
}
