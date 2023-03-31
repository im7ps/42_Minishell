/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_lv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:52:45 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 19:53:08 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_get_starting_shllv(t_list **envp)
{
	int				n;
	t_list			*env;

	n = 0;
	env = *envp;
	while (env != NULL)
	{
		if (!(ft_strncmp(env->key, "SHLVL", 6)))
		{
			n = ft_atoi(env->value);
		}
		env = env->next;
	}
	return (n);
}

char	ft_whatis(char c)
{
	if (ft_isdigit(c))
		return ('d');
	else if (ft_isalpha(c))
		return ('c');
	else if ((c < 48 && c > 32) || (c > 57 && c < 65) || \
		(c > 90 && c < 96) || (c > 122 && c < 127))
		return ('s');
	return (0);
}
