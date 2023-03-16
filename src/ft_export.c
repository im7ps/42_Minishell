/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:24 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/16 16:51:19 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_delete_quotes(char *value)
{
	int		i;
	int		counter;
	char	*newvalue;
	int		k;

	i = 0;
	counter = 0;
	while (value[i])
	{
		if (ft_is_escaped(value[i]) == 0)
		{
			counter++;
		}
		i++;
	}
	if (counter > 0)
	{
		newvalue = (char *) malloc (sizeof(char) * (counter + 1));
		if (!newvalue)
			return (NULL);
		k = 0;
		i = 0;
		while (value[i])
		{
			if (ft_is_escaped(value[i]) == 0)
			{
				newvalue[k] = value[i];
				k++;
			}
			i++;
		}
		newvalue[k] = '\0';
		free(value);
		return (newvalue);
	}
	return (value);	
}

void	ft_export_alone(t_list **envp)
{
	t_list *env;

	env = *envp;
	while (env)
	{
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

int	ft_export(t_list *head, t_list **envp, int **pipes, int index)
{
	int		i;
	int		j;
	int		k;
	t_list 	*new_node;
	t_list	*env;

	i = 0;
	if ((ft_strlen(head->cmd_m[0]) == 6 && ft_count_rows(head->cmd_m) == 1) && !(ft_strncmp(head->cmd_m[0], "export", 6)))
	{
		ft_export_alone(envp);
		return (0);
	}
	i = 1;
	while (head->cmd_m[i])
	{
		if (!(ft_strncmp(head->cmd_m[i], "|", 1)) || !(ft_strncmp(head->cmd_m[i], ">", 1)) || !(ft_strncmp(head->cmd_m[i], "<", 1)) || !(ft_strncmp(head->cmd_m[i], ">>", 2)) || !(ft_strncmp(head->cmd_m[i], "<<", 2)))
		{
			ft_printf("Ending with redirection\n");
			i++;
		}
		else
		{
			//controlla se il primo carattere è alfabetico o è un underscore, in tutti gli altri casi error
			j = 0;
			if ((!(ft_isalpha(head->cmd_m[i][j]))) || head->cmd_m[i][j] == '_')
			{
				ft_printf("error\n");
				return (1);
			}
			while (head->cmd_m[i][j])
			{
				if (head->cmd_m[i][j] == '=')
					break;
				j++;
			}
			//check se hanno inserito solo il nome della variabile, in tal caso stampa l env e poi il nome di tutte le variabili
			if (j >= ft_strlen(head->cmd_m[i]))
			{
				j = 0;
				env = *envp;
				ft_env(&env, pipes, index, head->cmd_m);
				while (head->cmd_m[i])
				{
					ft_printf("declare -x %s\n", head->cmd_m[i]);
					i++;
				}
				return (0);
			}
			//se la variabile non esiste, alloca un nuovo nodo alla lista envp con il relativo contenuto
			new_node = (t_list *) malloc (sizeof(t_list));
			if (new_node == NULL)
				return (1);

			new_node->key = ft_substr_old(head->cmd_m[i], 0, j);
			
			//check se la variabile nell env esiste giá, in tal caso il programma elimina il nodo relativo a quella variabile e ne alloca un'altra con il nuovo content
			ft_unset(NULL, envp, new_node->key);
			k = 0;
			while (head->cmd_m[i][j + k] != '\0')
			{
				k++;
			}
			new_node->value = ft_strndup((head->cmd_m[i] + j + 1), k);
			new_node->value = ft_delete_quotes(new_node->value);

			new_node->name = NULL;
			new_node->args = NULL;
			new_node->flags = NULL;
			new_node->end = NULL;
			new_node->next = NULL;
			ft_lstadd_back(envp, new_node);
			i++;
		}
	}
	return (0);
}