/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:10:59 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/03 15:46:53 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_perror(int err, char *cmd)
{
	if (err == ERR_NCMD)
		ft_printf("%s: Command not found!\n", cmd);
	if (err == ERR_QUOTE)
		ft_printf("Double quotes not closed properly!\n");
	if (err == ERR_INPUT)
		ft_printf("Character not valid!\n");
	return (1);
}