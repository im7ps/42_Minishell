/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:25:32 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 18:07:11 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

void	ft_CTRL_C_handler(int signum)
{
	write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void	ft_CTRL_D_handler(int signum)
{
	// printf("\r");
	// rl_on_new_line();
	// rl_redisplay();
	exit(0);
}

void	ft_CTRL_S_handler(int signum)
{
	return ;
}