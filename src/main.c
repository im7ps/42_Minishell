/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgioia <dgioia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/01/18 00:16:18 by dgioia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_cmd(char *output)
{
	char **cmd;

	cmd = ft_split(output, ' ');
	if(builtin(cmd))
		ft_perror(ERR_NCMD, cmd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*output;

	while (argc && argv)
	{
		output = readline("minishell> ");
		add_history(output);	
		check_cmd(output);
	}
	return (0);
}
