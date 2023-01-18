/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgioia <dgioia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:10:59 by dgioia            #+#    #+#             */
/*   Updated: 2023/01/18 00:16:58 by dgioia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_perror(int err, char *cmd)
{
	if (err == ERR_NCMD)
		printf("%s: Command not found!\n", cmd);
	if (err == ERR_QUOTE)
		printf("Double quotes not closed properly!\n");
	if (err == ERR_INPUT)
		printf("Character not valid!\n");
	return (1);
}