/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:36:45 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/19 21:59:53 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** FC_OPTION_detect()
** Va detecter quels options sont mises et les stocker dans un tableau.
** La fonction builtin_fc() va parcourir se tableau et lancer les fonction
** necessaires
*/

int		turn_on_option(char option, int *g_bit)
{
	if (option == 'e')
		*g_bit |= FC_OPTION_E;
	else if (option == 'l')
		*g_bit |= FC_OPTION_L;
	else if (option == 'n')
		*g_bit |= FC_OPTION_N;
	else if (option == 'r')
		*g_bit |= FC_OPTION_R;
	else if (option == 's')
		*g_bit |= FC_OPTION_S;
	else
	{
		ft_printf("42sh: bad option(s)\n");
		return (fc_error(0, NULL));
	}
	return (1);
}

int		option(char *s1, int *g_bit)
{
	s1++;
	if (*s1 == '-')
	{
		*g_bit |= FC_OPTION_STOP;
		return (1);
	}
	if (*s1 == '\0')
	{
		*g_bit |= FC_OPTION_END;
		return (1);
	}
	while (*s1)
	{
		if ((turn_on_option(*s1, g_bit)) == -1)
			return (0);
		s1++;
	}
	return (1);
}

/*
**Check_option: permet de boucler sur les arguments rentree en paramettre
**	par l'utilisateur. Si le paramettre commence par un "-" je verifie si c'est
**	une option valide. Si c'est le cas j'allume le bit correspondant grace a la
**	fonction "option" si ce n'est pas un arguments valide je retourne une
**	erreur.
** Cette fonction va aussi retourner l'emplacement du 1re argument dans le char
*/

int		check_fc_option(char **s1, int *g_bit)
{
	int i;

	i = 0;
	*g_bit = 0;
	while (s1[i])
	{
		if (s1[i++][0] == '\0')
			return (fc_error(0, NULL));
	}
	i = 0;
	while (s1[i] && !(*g_bit & FC_OPTION_STOP) && !(*g_bit & FC_OPTION_END))
	{
		if (s1[i][0] == '-' && ft_isalpha(s1[i][1]))
		{
			if (option(s1[i], g_bit) == 0)
				return (-1);
		}
		else
			break ;
		i++;
	}
	if (*g_bit & FC_OPTION_END)
		return (i - 1);
	else
		return (i);
}
