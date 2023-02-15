/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/15 21:37:03 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	int		i;
    t_list *new_node;
	
	i = 0;
	while (full_cmd[i])
	{
		new_node = ft_malloc_stuff(NODE_NUM);
		new_node->cmd_m = ft_split(full_cmd[i], ' ');
		new_node->name = NULL;
		new_node->args = NULL;
		new_node->flags = NULL;
		new_node->key = NULL;
		new_node->value = NULL;
		new_node->next = NULL;
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	return ;
}

void	ft_quotes_management(char	c, t_miniflags **minif)
{
	t_miniflags *flags;

	flags = *minif;
	if (c == 34 && !(flags->d_quote || flags->s_quote))
	{
		flags->d_quote = true;
		//ft_printf("dquotes activated\n");
	}
	else if (c == 39 && !(flags->d_quote || flags->s_quote))
	{
		flags->s_quote = true;
		//ft_printf("squotes activated\n");
	}
	else if (c == 34 && flags->d_quote)
	{
		flags->d_quote = false;
		//ft_printf("dquotes disabled\n");
	}
	else if (c == 39 && flags->s_quote)
	{
		flags->s_quote = false;
		//ft_printf("squotes disabled\n");
	}
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
			ft_printf("last char is -\n");
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
	int			len;
	char		type;
	
	i = 0;
	len = ft_count_rows(minip);
	ft_printf("%d\n", len);
	mini = *minip;
	while (mini->cmd_list)
	{
		
		ft_printf("NAME %s\n", mini->cmd_list->cmd_m[0]);
		i = 1;
		while (mini->cmd_list->cmd_m[i])
		{
			//differenziare se flag o argomento con una flag
			type = ft_choose_att(mini->cmd_list->cmd_m[i]);
			if (type == 'f' && i < len - 1)
				ft_printf("FLAGS: %s\n", mini->cmd_list->cmd_m[i]);
			else if (type == 'a' && i < len - 1)
				ft_printf("ARG: %s\n", mini->cmd_list->cmd_m[i]);
			i++;
		}
		ft_printf("ENDER %s\n", mini->cmd_list->cmd_m[i - 1]);
		mini->cmd_list = mini->cmd_list->next;
	}
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
	ft_create_list(&mini->cmd_list, mini->full_cmd);
	ft_set_attributes(&mini, &flags);
	//ft_dollar_expander(&mini);
	//ft_start_executing(&mini->cmd_list);
	return (0);
}
