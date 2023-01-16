/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgioia <dgioia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:10:59 by dgioia            #+#    #+#             */
/*   Updated: 2023/01/16 22:25:59 by dgioia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_perror(int err)
{
	if (err == ERR_NCMD)
		printf("MINISHELL: Command not found!\n");
	if (err == ERR_QUOTE)
		printf("MINISHELL: Double quotes not closed properly!\n");
	return (1);
}