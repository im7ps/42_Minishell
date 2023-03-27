/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/27 15:20:52 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_content_env(t_list **head, char *str)
{
	t_list	*tmp;

	tmp = (*head);
	while (tmp != NULL)
	{
		if (ft_strlen(str) == ft_strlen(tmp->key))
		{
			if (!ft_strncmp(str, tmp->key, ft_strlen(tmp->key)))
			{
				return(tmp->value);
			}
		}
		tmp = tmp->next;
	}
	return(NULL);
}

char *take_dollar(char *args, int i)
{
	int n;
	char *dollar;

	dollar = malloc(50000);
	n = 0;
	while(args[i])
	{
		if(args[i] == '$')
		{
			i++;
			if (args[i] == '?')
			{
				dollar[n++] = args[i];
				dollar[n] = '\0';
				return(dollar);
			}
			while (ft_isalnum(args[i]) && args[i])
				dollar[n++] = args[i++];
			dollar[n] = '\0';
			return(dollar);
		}
	}
	free(dollar);
	return(NULL);
}

char *take_env(char *args, t_list *env, int i)
{
	char *dollar;
	char *value;

	value = NULL;

	dollar = take_dollar(args, i);
	if (!ft_strncmp(dollar, "?", 1))
		value = ft_itoa(g_exit_status);
	else if (dollar != NULL)
	{
		value = search_content_env(&env, dollar);
		free(dollar);
		dollar = NULL;
	}
	return(value);
}

int do_dollar(char *tmp, char *args, t_list *env, int i)
{
	char *str;

	str = take_env(args, env, i);
	if (!tmp[0] && str != NULL)
		ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	else if (str != NULL && tmp != NULL)
		tmp = ft_strjoin(tmp, str, 0);
	i++;
	while ((ft_isalnum(args[i]) || args[i] == '?') && args[i])
	{
		if (args[i] == '?')
		{
			i++;
			break;
		}
		i++;
	}
	return(i);
}

bool ft_define_squotes(char c)
{
	int		qtoggle;
	bool	res;

	ft_is_escaped('r', 1);
	qtoggle = ft_is_escaped(c, 0);
	if (qtoggle == 2)
		res = true;
	else if (qtoggle == -2)
		res = false;
	return (res);
}

char *ft_dollar_expander(t_garbage **garbage, char *args, t_list *env)
{
	char *tmp;
	int i;
	int j;
	bool	squotes;

	if (ft_strlen(args) == 1 && args[0] == '$')
		return (args);
	tmp = gc_alloc(garbage, (sizeof(char) * 2048), 2048);
	i = 0;
	j = 0;
	while(args[i])
	{
		squotes = ft_define_squotes(args[i]);
		if (args[i] != '$' || squotes == true)
			tmp[j++] = args[i++];
		else if (args[i] == '$')
		{
			i = do_dollar(tmp + j, args, env, i);
			j = ft_strlen(tmp);
		}
	}
	tmp[ft_strlen(tmp)] = '\0';
	return(tmp);
}
