/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 14:13:40 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/20 13:41:58 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_error_flag(char *str, int i)
{
	st_printf("ls: illegal option -- %c\n", str[i]);
	st_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	exit(0);
}

void			set_flag(char *argv, int *flag)
{
	int		i;
	int		j;
	char	*str;
	int		bits;

	j = 0;
	i = 1;
	bits = 1;
	str = "aRltg1r";
	while (argv[i])
	{
		j = 0;
		bits = 1;
		while (str[j])
		{
			if (argv[i] == str[j])
			{
				*flag |= bits;
				break ;
			}
			j++;
			bits *= 2;
		}
		if (str[j] == '\0')
		{
			ft_error_flag(argv, i);
			return ;
		}
		i++;
	}
}

int				ft_flag(char **argv, int *flag)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			break ;
		if (ft_strequ(argv[i], "--"))
		{
			i++;
			break ;
		}
		if (argv[i][0] == '-' && argv[i][1])
			set_flag(argv[i], flag);
		else
			break ;
		i++;
	}
	return ((i < 0) ? 0 : i);
}
