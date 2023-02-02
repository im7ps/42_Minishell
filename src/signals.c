/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:25:32 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/02 21:29:24 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_CTRL_C_handler(int signum)
{
	t_minishell	*mini;

	mini = ft_get_mini(NULL);
	ft_execute_mini(&mini);
}

void	ft_CTRL_D_handler(int signum)
{
	exit(0);
}

void	ft_CTRL_S_handler(int signum)
{
	return ;
}