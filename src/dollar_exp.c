/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/10 17:32:22 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_dollar_starter(t_list **envp, char  *str, int i)
{
	int len;
	int	smaller;
	t_list *envp_p;
	char	*value_copy;

	len = 0;
	smaller = 0;
	envp_p = *envp;
	if (i + 1 < ft_strlen(str))
	{
		i++;
		while (((str[i + len] > 64 && str[i + len] < 91) || str[i + len] == 95) && str[i + len] != '\0')
		{
			len++;
		}
	}

	while (envp_p != NULL)
	{
		if (len == ft_strlen(envp_p->key))
		{
			if (!(ft_strncmp(str + 1, envp_p->key, len)))
			{
				value_copy = malloc(sizeof(char) * ft_strlen(envp_p->value) + 1);
				ft_strlcpy(value_copy, envp_p->value, ft_strlen(envp_p->value) + 1);
				free(str);
				return (value_copy);
			}
		}
		envp_p = envp_p->next;
	}
	return (NULL);
}
/*
char	*ft_dollar_expander(t_list **envp, char *str)
{
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_dollar_starter(envp, str, i);
			if (tmp != NULL)
			{
				return (tmp);
			}
			else
			{
				return (str + i);
			}
		}
		i++;
	}
	return (str);
}
*/


char	*ft_dollar_expander(t_list **envp, char *str)
{
	int			i;
	int			j;
	char		*tmp;
	int			quotes = 0;
	int			toggle;

	toggle = 1;
	i = 0;
	while (str[i])
	{
		quotes = ft_is_escaped(str[i]);
		if (quotes == 2 || quotes == -2 || quotes == -3)
		{
			toggle = toggle * -1;
		}
		if (str[i] == '$' && toggle != -1)
		{
			tmp = ft_dollar_starter(envp, str, i);
			if (tmp != NULL)
			{
				return (tmp);
			}
			else
			{
				return (str + i);
			}
		}
		i++;
	}
	return (str);
}

