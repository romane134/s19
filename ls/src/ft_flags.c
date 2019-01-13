/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:33:09 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/08 12:33:50 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_choose_flag(char *argv, t_flag flag)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i] == 'l')
			*flag |= L_FLAGS; //envoyer un pointeur sur flag pour qu'on puisse recuperer les infos partout dans le fichier
		if (argv[i] == 'R')
			*flag |= RR_FLAGS;
		if (argv[i] == 'a')
			*flag |= A_FLAGS;
		if (argv[i] == 'r')
			*flag |= R_FLAGS;
		if (argv[i] == 't')
			*flag |= T_FLAGS;
		if (argv[i] == 'n')
			*flag |= N_FLAGS;
		if (argv[i] == 'g')
			*flag |= G_FLAG;
		if (argv[i] == '1')
			*flag |= 1_FLAGS;
		if (argv[i] == 'C')
			*flag |= CC_FLAGS;
		if (argv[i] == 'U')
			*flag |= UU_FLAGS;
		if (argv[i] == 'A')
			*flag |= AA_FLAGS;
		i++;
	}


}
int		ft_flag(char **argv, t_flag flag)
{
	int i;

	i = 0;
	while (argv[i++])
	{
		if (argv[i][0] != '-')
			break;
		if (argv[i][0] == '-' && argv[i][1])
			ft_choose_flag(argv[i], flag);
		else
			break;
	}
	return (i + 1) //pas sure 

}
