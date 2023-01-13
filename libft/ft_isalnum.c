/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:20:52 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 18:35:29 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The isalnum() function checks whether the argument passed is an alphanumeric character (alphabet or number) or not.
//fonte: https://www.programiz.com/c-programming/library-function/ctype.h/isalnum

int	ft_isalnum(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58))
		return (1);															//Returns 1 if argument is an alphanumeric character.
	else
		return (0);															//Returns 0 if argument is neither an alphabet nor a digit.
}
