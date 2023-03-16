/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:08 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/16 19:50:50 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_trypath(char	*cmd, t_list **envp)
{
	t_list 	*env;
	char	**trypath;
	char	*cmdcopy;
	int		i;

	i = 0;
	env = *envp;
	while (env)
	{
		if (!(ft_strncmp("PATH", env->key, 4)))
		{
			trypath = ft_old_split(env->value, ':');
		}
		i++;
		env = env->next;
	}

	cmdcopy = cmd;

	i = 0;
	while (trypath[i])
	{
		trypath[i] = ft_strjoin(trypath[i], "/", 0);
		cmd = ft_strjoin(trypath[i], cmd, 0);
		if (access(cmd, X_OK) == 0)
		{
			ft_printf("found: %s\n", cmd);
			return (cmd);
		}
		else
		{
			//ft_printf("Not found!\n");
			cmd = cmdcopy;
		}
		i++;
	}
	return (NULL);
}

void	ft_clean_all(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;

	mini = *minip;
	flags = *minif;
	free_stuff(NULL, NULL, &mini->envp_list, flags);
	free_stuff(NULL, NULL, &mini->cmd_list, NULL);
	free_stuff(NULL, NULL, &mini->envp_list, NULL);
}

int	free_stuff(t_list *node, char **matrix, t_list **stack, t_miniflags *flags)
{
	int	i;

	i = 0;
	if (node != NULL)
	{
		free(node);
		node = NULL;
	}
	if (matrix != NULL)
	{
		while (matrix[i])
		{
			//ft_printf("FREE %p\n", matrix[i]);
			free(matrix[i++]);
		}
		free(matrix);
		matrix = NULL;
	}
	if (stack != NULL)
	{
		ft_lst_delete(stack);
	}
	if (flags != NULL)
	{
		free(flags);
		flags = NULL;
	}
	return (0);
}

void	ft_lst_delete(t_list **stack)
{
	t_list	*tmp;

	if (*stack == NULL)
		return ;
	tmp = *stack;
	while (*stack != NULL)
	{
		tmp = (*stack)->next;
		free (*stack);
		*stack = tmp;
	}
}

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

int	ft_count_commands(t_list **cmd_list)
{
	t_list	*head;
	int		i;

	i = 0;
	head = *cmd_list;
	while(head)
	{
		i++;
		head = head->next;
	}
	return (i);
}
