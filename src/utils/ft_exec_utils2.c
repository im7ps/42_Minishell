/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 21:01:04 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:15:23 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_dedicated(char *str)
{
	if (!(ft_strncmp(str, "exit", 4)))
		return (0);
	else if (!(ft_strncmp(str, "./minishell", 11)))
		return (0);
	return (1);
}
