/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:33:01 by bjovanov          #+#    #+#             */
/*   Updated: 2019/06/20 19:33:02 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		nflag(char **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] != '-')
			return (i);
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int		builtin_echo(char **cmd)
{
	int i;
	int iteration;
	int flag;

	iteration = 0;
	i = nflag(cmd);
	flag = (i > 0) ? 1 : 0;
	while (cmd[i])
	{
		if (iteration > 0)
			ft_printf(" ");
		ft_printf("%s", cmd[i]);
		i++;
		iteration++;
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}
