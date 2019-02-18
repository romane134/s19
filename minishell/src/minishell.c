/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:47:40 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/18 13:49:00 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

void		ft_sig(int i)
{
	i = 2;
	prompt(i);
}

void		prompt(int i)
{
	if (i == 2)
		st_printf("\n");
	st_printf("Romane$>");
}

int			main(int argc, char **argv)
{
	char		*line;

	signal(SIGINT, ft_sig);
	if (argc == 1 && argv)
		while (1)
		{
			prompt(0);
			get_next_line(0, &line);
			if ((ft_strcmp(line, "exit") == 0))
				break ;
			msh_message(line, argv);
			free(line);
		}
	return (0);
}

