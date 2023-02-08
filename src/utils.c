/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:08 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/08 14:45:05 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t ft_smaller_string(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str2));
	else
		return (ft_strlen(str1));
}

void	ft_free_stuff(t_minishell *mini, char *str)
{
	if (str)
		free(str);
	if (mini)
		free(mini);
	return ;
}

int	ft_strerr(char *str)
{
	int	i;

	i = 0;
	write(1, str, ft_strlen(str));
	return (1);
}

t_minishell *ft_get_mini(t_minishell *mini)
{
	static t_minishell *mini_s;
	if (mini != NULL)
	{
		mini_s = mini;
	}
	return (mini_s);
}
