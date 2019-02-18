/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:58:43 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/18 13:48:55 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdio.h>

void			msh_echo(char *line)
{
	char	**echo;
	int		flag;
	int		len;
	int		j;

	j = 2;
	flag = 0;
	len = 0;
	if (ft_strcmp(line, "echo") >= 0)
		echo = ft_strsplit(line, ' ');
	else
		return ;
	while (echo[len])
		len++;
	if ((echo[1][0] == '-') && (echo[1][1] == 'n'))
	{
		while (len > 2)
		{
			st_printf("%s ", echo[j]);
			j++;
			len--;
		}
			st_printf("%s", echo[j]);
	}
	else
	{
		j = 1;
		while ((*echo) && (len > 2))
		{
			st_printf("%s ", echo[j++]);
			len--;
		}
		st_printf ("%s\n", echo[j]);
	}
}

	int				main(int argc, char **argv)
	{
		if (argc)
			ft_echo(argv[1]);
		return (0);
	}
