/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:51:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/25 15:58:48 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	*search_content_env(t_list **head, char *str)
// {
// 	t_list	*tmp;
// 	char	*value;
// 	int		len;

// 	len = 0;
// 	while (ft_isalnum(str[len]))
// 		len++;
// 	tmp = (*head);
// 	while (tmp != NULL)
// 	{
// 		if (ft_strlen(tmp->key) == len)
// 		{
// 			if (!ft_strncmp(tmp->key, str, ft_strlen(tmp->key)))
// 			{
// 				value = (char *) malloc (sizeof(char) * (ft_strlen(tmp->value) + 1));
// 				ft_strlcpy(value, tmp->value, ft_strlen(tmp->value) + 1);
// 				value[ft_strlen(tmp->value)] = '\0';
// 				return(value);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return(NULL);
// }
// char *take_dollar(char *args, int i)
// {
// 	char *dollar;
// 	int j;

// 	j = 0;
// 	dollar = malloc(50000);
// 	i++;
// 	while(args[i] != '$' && args[i])
// 		dollar[j++] = args[i++];		
// 	return(dollar);
// }

// char *take_env(char *args, t_list **envp, int i)
// {
// 	char *value;
// 	char *predollar;
// 	int j;
// 	int after;
// 	char *dollar;

// 	j = 0;
// 	after = 0;
// 	while(args[j] != '$')
// 		j++;
// 	if (j != 0)
// 	{
// 		predollar = (char *) malloc (sizeof(char) * (j + 1));
// 		predollar[j] = '\0';
// 		ft_strlcpy(predollar, args, j + 1);
// 	}
// 	while (ft_isalnum(args[j + (++after)]))
// 		;
// 	dollar = take_dollar(args, j);
// 	value = search_content_env(envp, dollar);
// 	if (j != 0)
// 	{
// 		if (!value)
// 		{
// 			value = predollar;
// 		}
// 		else if (value && predollar)
// 			value = ft_strjoin(predollar, value, 0);
// 	}
// 	if (after != 1)
// 	{
// 		if (!value)
// 			value = args + j + after;
// 		else if (value && (args + j + after))
// 			value = ft_strjoin(value, args + j + after, 0);
		
// 	}
// 	return(value);
// }

// char	*ft_dollar_starter(t_list **envp, char  *str)
// {
// 	int 	len;
// 	char	*string_final;
// 	char	**matrix;
// 	char	*tmp;
// 	int		i;

// 	if (str[0] == '"')
// 	{
// 		matrix = ft_old_split(str, ' ');		
// 		i = 0;
// 		while (matrix[i])
// 		{
// 			//se nella stringa é presente un dollaro prova a espanderlo e vai avanti
// 			if (ft_strchr(matrix[i], '$'))
// 			{
// 				// tmp = ft_expander(matrix[i], envp);
// 				tmp = take_env(matrix[i], envp, 0);
// 			}
// 			//se nella stringa non é presente un dollaro allora joina per creare la stringa finale, sennó joina la stringa espansa
// 			else
// 			{
// 				tmp = (char *) malloc (sizeof(char) * (ft_strlen(matrix[i]) + 1));
// 				tmp[ft_strlen(matrix[i])] = '\0';
// 				ft_strlcpy(tmp, matrix[i], ft_strlen(matrix[i]) + 1);
// 			}
// 			//crea la stringa finale unendo tmp espanso o tmp normale
// 			if (i == 0)
// 				string_final = ft_strjoin(string_final, tmp, 1);
// 			else
// 				string_final = ft_strjoin(string_final, tmp, 0);
// 			string_final = ft_strjoin(string_final, " ", 0);
// 			free(tmp);
// 			i++;
// 		}
// 		if (string_final)
// 			return (string_final);
// 	}
// 	else
// 	{
// 		if (ft_strchr(str, '$'))
// 		{
// 			// tmp = ft_expander(matrix[i], envp);
// 			str = take_env(str, envp, 0);
// 		}
// 		return (str);
// 	}
// 	return (NULL);
// }

// //se nella stringa str é presente un dollaro + variabile della forma $VAR che non é fra single quotes "/'" allora trova il valore di VAR nella lista envp e sostituiscilo
// char	*ft_dollar_expander(t_list **envp, char *str)
// {
// 	int			i;
// 	int			quotes;
// 	bool		in_dquotes;
// 	bool		in_squotes;
// 	char		*tmp;
	

// 	in_dquotes = false;
// 	in_squotes = false;
// 	i = 0;
// 	while (str[i])
// 	{
// 		// controlla le virgolette
// 		if (i == 0)
// 		{
// 			quotes = ft_is_escaped(str[i], 1);
// 		}
// 		else
// 		{
// 			quotes = ft_is_escaped(str[i], 0);
// 		}
// 		if (quotes == 1)
// 			in_dquotes = !in_dquotes;
// 		else if (quotes == 2)
// 			in_squotes = !in_squotes;
// 		else if (quotes == -1)
// 			in_dquotes = false;
// 		else if (quotes == -2)
// 			in_squotes = false;

// 		if (str[i] == '$' && !in_squotes && !(in_dquotes && str[i] == 39))
// 		{
// 			str = ft_dollar_starter(envp, str);
// 			break;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

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

int do_dollar(char *tmp, char *args, t_list *env)
{
	char i;
	char *str;

	i = 0;
	str = take_env(args, env, i);
	if (i == 0 && str != NULL)
		ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	else if (str != NULL && tmp != NULL)
		tmp = ft_strjoin(tmp, str, 0);
	*args++;
	i++;
	while ((ft_isalnum(*args) || *args == '?') && *args != '\0')
	{
		if (*args == '?')
			break;
		i++;
		args++;
	}
	return(i);
}

bool ft_define_squotes(char c)
{
	int		qtoggle;

	ft_is_escaped('r', 1);
	qtoggle = ft_is_escaped(c, 0);
	if (qtoggle == 2)
		return (true);
	else if (qtoggle == -2)
		return (false);
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
			i += do_dollar(tmp + j, args + i, env);
	}
	tmp[ft_strlen(tmp)] = '\0';
	return(tmp);
}
