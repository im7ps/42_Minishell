/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:11:21 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/30 23:29:24 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int g_exit_status;

int	ft_set_exit_status(int value)
{
	if (value == 1)
		g_exit_status = 1;
	else if (value == 256)
		g_exit_status = 1;
	else if (value == 2)
		g_exit_status = 130;
	else if (value == 0)
		g_exit_status = 0;
	return (g_exit_status);
}