/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/03 18:31:01 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*	confronta str con la lista di variabili d'ambiente storata in minip.envp, se c'é
*	corrispondenza allora ritorna la value della key trovata, in caso contrario ritorna NULL
*/
char    *ft_expander_finder(t_minishell **minip, int i, char *input)
{
	size_t      smaller;
	t_list      *mini;
	char		str[i];

	ft_printf("%s\n", input);
	ft_strlcpy(str, input, i);
	ft_printf("%s\n", str);
	mini = (*minip)->envp_list;
	while (mini)
	{
		smaller = ft_smaller_string(str, mini->key);
		if (ft_strlen(str) + 1 == ft_strlen(mini->key))
		{
			if (!(ft_strncmp(str, mini->key, smaller)))
			{
				return (mini->value);
			}
		}
		mini = mini->next;
	}
	return (NULL);
}

/*
*	ft_expander_helper:
*	scorri la stringa trovata dopo il $, alloca una stringa temporanea e avvia ft_expander_helper
*	se la stringa ritornata é diversa da NULL ritorna il valore aggiornato di tmp
*/
char    *ft_expander_helper(t_minishell **minip, char *input)
{
	t_minishell *mini;
	int     	i;
	char    	*tmp;

	mini = *minip;
	i = 0;
	while (((input[i] > 64 && input[i] < 91) || input[i] == 95) && input[i] != '\0')
	{
		i++;
	}
	tmp = ft_expander_finder(&mini, i + 1, input);
	if (tmp == NULL)
		return (NULL);
	//printf("EXPANDED: %s\n", tmp);
	return (tmp);
}

/*
*	ft_dollar_starter:
*	scansiona la stringa, quando trovi il dollaro assicurati che il carattere seguente
*	sia in maiuscolo o sia un underscore, in caso affermativo avvia ft_expander_helper
*	se il valore ritornato é non NULL aggiorna la stringa da ritornare, in caso
*	contrario ritorna NULL
*/
char	*ft_dollar_starter(t_list **envp, char  *str, int i)
{
	int len;
	int	smaller;
	t_list *envp_p;

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
				return (envp_p->value);
			}
		}
		envp_p = envp_p->next;
	}
	return (NULL);
}

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
			//ft_printf("K %s V %s\n", (*envp)->key, (*envp)->value);
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

