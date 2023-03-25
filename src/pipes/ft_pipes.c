/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:04:37 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/24 19:00:20 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Funzione esterna per la parte 1
void open_pipes(int **pipes, int cmd_num) 
{
    int i = 0;
    while(i < cmd_num + 1) 
	{
        pipes[i] = (int *) malloc (sizeof(int) * 2);
        if (pipe(pipes[i]) == -1) 
		{
            ft_printf("Error with creating pipe\n");
            return;
        }
        i++;
    }
}

// Funzione esterna per la parte 2
void close_pipes(int **pipes, int cmd_num) 
{
    int i = 0;
    while (i < cmd_num + 1) 
	{
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}
