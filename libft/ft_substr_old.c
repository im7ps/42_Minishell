/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:58:47 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/08 23:59:24 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

char	*ft_substr_old(char const *s, unsigned int start, int len)
{
	char	*stack;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		start = ft_strlen(s);
	if (ft_strlen(s) <= start + len)
	{
		len = ft_strlen(s) - start;
	}
	stack = (char *) malloc (sizeof(char) * (len + 1));		//MINISHELL: +2 per contenere EOF e char reindirizzamento (| < > << >>)
	if (!stack)
		return (NULL);
	while (len--)										//MINISHELL: 1 + len-- (it was len--) per fargli includere la redirection nella stringa, che altrimenti verrebbe ignorata essendo il char separatore
		stack[i++] = s[start++];								//MINISHELL: stack[i] = '\0'; era l originale, cambiato per mettere in pos stack[i] il reindirizzamento
	stack[i] = '\0';
	return (stack);
}
