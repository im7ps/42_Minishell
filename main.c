/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:45:51 by sgerace           #+#    #+#             */
/*   Updated: 2022/12/02 20:36:30 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_stuff(const char *input)
{
	if (input)
		free(&input);
	rl_clear_history();
}

int	main(int argc, const char **argv)
{
	const char	*prompt;
	const char	*input;

	prompt = "minishell> ";
	input = readline(prompt);
	add_history(input);

	printf("%s\n", input);
	readline(prompt);
	ft_free_stuff(const char *input);
	return (0);
}
