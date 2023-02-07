/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 17:08:19 by sgerace          ###   ########.fr       */
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

/*
*	confronta str con la lista di variabili d'ambiente storata in minip.envp, se c'é
*	corrispondenza allora ritorna la value della key trovata, in caso contrario ritorna NULL
*/
char    *ft_expander_finder(char *str, t_minishell **minip)
{
	size_t      smaller;
	t_list      *mini;

	mini = (*minip)->envp_list;
	while (mini)
	{
		smaller = ft_smaller_string(str, mini->key);
		if (ft_strlen(str) == ft_strlen(mini->key))
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
	tmp = (char *) malloc (sizeof(char) * i + 1);
	ft_strlcpy(tmp, input, i + 1);
	tmp = ft_expander_finder(tmp, &mini);
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
char	*ft_dollar_starter(t_minishell **minip, char  *str)
{
	t_minishell *mini;
	int			i;
	int 		len;

	mini = *minip;
	i = -1;
	len = ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (i + 1 < len)
			{
				i++;
				if (!((str[i] > 64 && str[i] < 91) || str[i] == 95))
					return (NULL);
				str = ft_expander_helper(&mini, str + i);
				if (str == NULL)
					return (NULL);
			}
		}
	}
	return (str);
}

/*  
*   ft_dollar_expander: 
*	scansiona ogni elemento della matrice di comandi, se in un elemento é presente il dollaro
*	avvia dollar_starter, se la funziona ritorna un valore non NULL aggiorna il valore
*	della stringa
*/
char	*ft_dollar_expander(t_minishell **minip)
{
	t_minishell	*mini;
	t_list 		*cmd_list;
	int			i;
	int			j;
	char		*tmp;

	cmd_list = (*minip)->cmd_list;
	mini = *minip;
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd_m[i])
		{
			j = 0;
			while (cmd_list->cmd_m[i][j])
			{
				if (cmd_list->cmd_m[i][j] == '$')
					tmp = ft_dollar_starter(&mini, cmd_list->cmd_m[i]);
					if (tmp != NULL)
						cmd_list->cmd_m[i] = tmp;
				j++;
			}
			i++;
		}
		cmd_list = cmd_list->next;
	}
	return (mini->input);
}