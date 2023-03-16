/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/16 21:23:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_content_env(t_list **head, char *str)
{
	t_list	*tmp;
	char	*value; 

	tmp = (*head);
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(tmp->key)))
		{
			value = (char *) malloc (sizeof(char) * (ft_strlen(tmp->value) + 1));
			ft_strlcpy(value, tmp->value, ft_strlen(tmp->value) + 1);
			value[ft_strlen(tmp->value)] = '\0';
			return(value);
		}
		tmp = tmp->next;
	}
	return(NULL);
}

char *take_env(char *args, t_list **envp, int i)
{
	char *value;
	char *predollar;
	int j;
	int after;

	j = 0;
	after = 0;

	while(args[j] != '$')
	{
		j++;
	}
	if (j != 0)
	{
		predollar = (char *) malloc (sizeof(char) * (j + 1));
		predollar[j] = '\0';
		ft_strlcpy(predollar, args, j + 1);
	}
	while (ft_isalnum(args[j + (++after)]))
		;
	ft_printf("Post dollar %s\n", args + j + after);
	if (after != 1)
	{
		value = NULL;
	}
	else
	{
		value = search_content_env(envp, args + j + 1);
	}
	if (j != 0)
	{
		value = ft_strjoin(predollar, value, 2);
	}
	if (after != 1)
	{
		value = ft_strjoin(value, args + j + after, 0);
	}
	return(value);
}

char	*ft_expander(char *str, t_list **envp)
{
	t_list *env;
	int		i;
	char	*before_dollar;

	env = *envp;
	i = 0;

	while (str[i] != '$')
	{
		i++;
	}
	if (i != 0)
	{
		before_dollar = (char *) malloc (sizeof(char) * (i + 1));
		before_dollar[i] = '\0';
		ft_strlcpy(before_dollar, str, i + 1);
		ft_printf("Devo espandere: %s\n", before_dollar);
	}

	// while (envp_p != NULL)
	// {
	// 	if (len == ft_strlen(envp_p->key))
	// 	{
	// 		if (!(ft_strncmp(str + 1, envp_p->key, len)))
	// 		{
	// 			value_copy = malloc(sizeof(char) * ft_strlen(envp_p->value) + 1);
	// 			ft_strlcpy(value_copy, envp_p->value, ft_strlen(envp_p->value) + 1);
	// 			free(str);
	// 			return (value_copy);
	// 		}
	// 	}
	// 	envp_p = envp_p->next;
	// }


	// if (before_dollar)
	// 	free(before_dollar);
	return (NULL);
}

char	*ft_dollar_starter(t_list **envp, char  *str)
{
	int 	len;
	char	*string_final;
	char	**matrix;
	char	*tmp;
	int		i;

	if (str[0] == '"')
	{
		matrix = ft_old_split(str, ' ');		
		i = 0;
		while (matrix[i])
		{
			//se nella stringa é presente un dollaro prova a espanderlo e vai avanti
			if (ft_strchr(matrix[i], '$'))
			{
				// tmp = ft_expander(matrix[i], envp);
				tmp = take_env(matrix[i], envp, 0);
			}
			//se nella stringa non é presente un dollaro allora joina per creare la stringa finale, sennó joina la stringa espansa
			else
			{
				tmp = (char *) malloc (sizeof(char) * (ft_strlen(matrix[i]) + 1));
				tmp[ft_strlen(matrix[i])] = '\0';
				ft_strlcpy(tmp, matrix[i], ft_strlen(matrix[i]) + 1);
			}
			//crea la stringa finale unendo tmp espanso o tmp normale
			if (i == 0)
				string_final = ft_strjoin(string_final, tmp, 1);
			else
				string_final = ft_strjoin(string_final, tmp, 0);
			string_final = ft_strjoin(string_final, " ", 0);
			free(tmp);
			i++;
		}
		if (string_final)
			return (string_final);
	}
	else
	{
		if (ft_strchr(str, '$'))
		{
			// tmp = ft_expander(matrix[i], envp);
			str = take_env(str, envp, 0);
		}
		return (str);
	}
	return (NULL);
}

//se nella stringa str é presente un dollaro + variabile della forma $VAR che non é fra single quotes "/'" allora trova il valore di VAR nella lista envp e sostituiscilo
char	*ft_dollar_expander(t_list **envp, char *str)
{
	int			i;
	int			quotes;
	bool		in_dquotes;
	bool		in_squotes;
	char		*tmp;
	

	in_dquotes = false;
	in_squotes = false;
	i = 0;
	while (str[i])
	{
		// controlla le virgolette
		quotes = ft_is_escaped(str[i]);
		if (quotes == 1)
			in_dquotes = !in_dquotes;
		else if (quotes == 2)
			in_squotes = !in_squotes;
		else if (quotes == -1)
			in_dquotes = false;
		else if (quotes == -2)
			in_squotes = false;

		if (str[i] == '$' && !in_squotes && !(in_dquotes && str[i + 1] == '\''))
		{
			str = ft_dollar_starter(envp, str);
			break;
		}
		i++;
	}
	return (str);
}

