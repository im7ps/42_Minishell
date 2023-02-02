/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:08 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/02 19:56:31 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	ft_invalid_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

t_minishell *ft_get_mini(t_minishell *mini)
{
	static t_minishell *mini_s;
	if (mini != NULL)
	{
		//mini_s = (t_minishell *) malloc (sizeof(t_minishell));
		mini_s = mini;
	}
	return (mini_s);
}
