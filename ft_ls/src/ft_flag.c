/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 14:13:40 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 16:48:09 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_error_flag(char *str, int i)
{
	st_printf_error("ls: illegal option -- %c\n", str[i]);
	st_printf_error("usage: ls \
[-aRltg1rTuUnsf] [file ...]\n");
	exit(0);
}

int				set_flag_2(char *argv, int *i, int *flag, int bits)
{
	char	*str;

	str = "aRltg1rTuUnsf";
	while (str[i[1]])
	{
		if (argv[i[0]] == str[i[1]])
		{
			*flag |= bits;
			break ;
		}
		i[1]++;
		bits *= 2;
	}
	if (str[i[1]] == '\0')
	{
		ft_error_flag(argv, i[0]);
		return (0);
	}
	return (1);
}

void			set_flag(char *argv, int *flag)
{
	int		i[2];
	int		bits;

	i[0] = 1;
	bits = 1;
	while (argv[i[0]])
	{
		i[1] = 0;
		bits = 1;
		if (argv[i[0]] == 'n')
			*flag |= 4;
		else if (argv[i[0]] == 'f')
			*flag |= 1;
		if ((set_flag_2(argv, i, flag, bits) == 0))
			return ;
		i[0]++;
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
		if ((argv[i][0] == '-' && argv[i][1]) && (!(ft_strequ(argv[i], "--"))))
			set_flag(argv[i], flag);
		if (ft_strequ(argv[i], "--"))
		{
			i++;
			break ;
		}
		else if ((argv[i][0] == '-' && (argv[i][1]) == '\0'))
			break ;
		i++;
	}
	return ((i < 0) ? 0 : (i));
}
