/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/03 18:35:01 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list *ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	int		i;
	int		j;
    t_list *new_node;
	
	i = 0;
	while (full_cmd[i])
	{
		ft_printf("FCMD %s\n", full_cmd[i]);
		ft_printf("FCMD %p\n", full_cmd[i]);
		j = 0;	
		new_node = (t_list*) malloc(sizeof(t_list));
		new_node->cmd_m = ft_split(full_cmd[i], ' ');
		ft_printf("ADDRESS NODE %p\n", new_node);
		ft_printf("STRING NODE %s\n", new_node->cmd_m[0]);
		while (new_node->cmd_m[j])
		{
			//ft_printf("%p\n", new_node->cmd_m[j]);
			//ft_printf("%s\n", new_node->cmd_m[j]);
			if (new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] == ' ')
				new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] = '\0';	//l ultimo char é uno spazio, sicuramente dovuto allo split
			j++;
		}
		new_node->name = NULL;
		new_node->args = NULL;
		new_node->flags = NULL;
		new_node->key = NULL;
		new_node->value = NULL;
		new_node->next = NULL;
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	free_stuff(NULL, full_cmd, NULL, NULL);
	return (*cmd_list);
}

char	ft_choose_att(char	*str)
{
	int		i;
	int		len;
	char	type;
	int		toggle;

	i = 0;
	toggle = 0;
	len = ft_strlen(str);
	if (str[0] != '-' && str[0] != '\'' && str[i] != '"')
	{
		type = 'a';
		return (type);
	}
	else if (str[i] == '\'')
	{
		toggle = 1;
		while(str[i] == '\'')
			i++;
	}
	else if (str[i] == '"')
	{
		toggle = 2;
		while(str[i] == '"')
			i++;
	}
	else if (str[i] == ' ')
	{
		while(str[i] == ' ')
			i++;
	}
	if (str[i] == '-')
	{
		if (i + 1 < len)
		{
			i++;
			if (str[i] == 'n')
			{
				while (str[i])
				{
					if (str[i] != 'n')
					{
						if ((str[i] == ' ' && i == len - 1))
						{
							type = 'f';
							return (type);
						}
						type = 'a';
						return (type);
					}
					i++;
				}
			}
			else
			{
				type = 'a';
				return (type);
			}
		}
		else
		{
			//ft_printf("last char is -\n");
			type = 'a';
			return (type);
		}
			
	}
	type = 'f';
	return (type);
}

int		ft_count_rows(t_minishell **minip)
{
	int i;
	t_minishell *mini;

	i = 0;
	mini = *minip;
	while (mini->cmd_list->cmd_m[i])
	{
		i++;
	}
	return (i);
}

void	ft_set_attributes(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	int			i;
	int			j;
	int			len;
	char		type;
	
	i = 0;
	len = ft_count_rows(minip);
	//mini->cmd_list->flags = (char **) malloc (sizeof(char *) * len);
	// mini = *minip;
	// while (mini->cmd_list)
	// {
	// 	mini->cmd_list->name = mini->cmd_list->cmd_m[0];
	// 	ft_printf("NAME %s\n", mini->cmd_list->name);
	// 	i = 1;
	// 	// j = 0;
	// 	while (mini->cmd_list->cmd_m[i])
	// 	{
	// 		//differenziare se flag o argomento con una flag
	// 		// type = ft_choose_att(mini->cmd_list->cmd_m[i]);
	// 		// if (type == 'f' && i < len - 1)
	// 		// {
	// 		// 	mini->cmd_list->flags = mini->cmd_list->cmd_m[i];
	// 		// 	j++;
	// 		// }
	// 		// else if (type == 'a' && i < len - 1)
	// 		ft_printf("ATTR %s\n", mini->cmd_list->cmd_m[i]);
	// 		i++;
	// 	}
	// 	ft_printf("ENDER %s\n", mini->cmd_list->cmd_m[i - 1]);
	// 	mini->cmd_list = mini->cmd_list->next;
	// }
}

int	ft_parser(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;
	int			cmd_num;
	int			i;

	mini = *minip;
	flags = *minif;
	mini->full_cmd = ft_split_variant(mini->input);
	mini->cmd_list = ft_create_list(&mini->cmd_list, mini->full_cmd);
	/*mini = *minip;
	while (mini->cmd_list)
	{
		i = 0;
		while (mini->cmd_list->cmd_m[i])
		{
			//ft_printf("CHECK %s\n", mini->cmd_list->cmd_m[i]);
			mini->cmd_list->cmd_m[i] = ft_dollar_expander(&mini->envp_list, mini->cmd_list->cmd_m[i]);
			if (mini->cmd_list->cmd_m[i] == NULL)
			{
				ft_printf("Sus\n");
			}
			ft_printf("DOLLAR %s\n", mini->cmd_list->cmd_m[i]);
			i++;
		}
		mini->cmd_list = mini->cmd_list->next;
	}*/
	/*mini = *minip;
	ft_printf("DOLLAR %s\n", mini->cmd_list->cmd_m[0]);
	ft_printf("DOLLAR %s\n", mini->cmd_list->cmd_m[1]);
	ft_printf("DOLLAR %s\n", mini->cmd_list->cmd_m[2]);*/
	return (0);
}
