/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_option_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:53:10 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/19 22:03:03 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** fc_print_line()
**
** On va aller recup la ligne dans l'historique en pos-1
** Si on est en -l on l'affiche, si -n on affiche pos (Attention pos commence a
**< 1)
** c'est pour cela qu'on va chercher pos - 1 car l'historique commence a 0.
** Si jamais on a pas le -n on ecrit la ligne dans le fichier precedement ouvert
*/

void	fc_print_line(int pos, int g_bit, int fd)
{
	char *result;

	result = read_last_line(pos - 1);
	if ((g_bit & FC_OPTION_L))
	{
		if (!(g_bit & FC_OPTION_N))
			ft_printf("%d", pos);
		ft_printf("\t%s\n", result);
	}
	else
	{
		write(fd, result, ft_strlen(result));
		write(fd, "\n", 1);
	}
	ft_strdel(&result);
}

/*
** fc_increase()
** On incremente ou decremente le compteur de la position dans l'histo qu'on
** ecrit
*/

void	fc_increase(int first, int last, int g_bit, int fd)
{
	while (first <= last)
		fc_print_line(first++, g_bit, fd);
}

/*
** fc_decrease()
** On incremente ou decremente le compteur de la position dans l'histo qu'on
** ecrit
*/

void	fc_decrease(int first, int last, int g_bit, int fd)
{
	while (first >= last)
		fc_print_line(first--, g_bit, fd);
}

/*
** fc_option_l()
**
** Recup first et last
** !!(first doit etre a 0 pour dire qu'il faut en renvoyer 16 si il n'y a
** 	pas de first) !!
** Si on a -r on inverse firrst et last
** En fonction de qui est le plus grand on choisi le sens dans lequel on lit
** l'historique
*/

int		fc_option_l(char **cmd, int g_bit, int i, int fd)
{
	int first;
	int last;
	int history_len_tmp;

	first = fd;
	get_first_last(cmd, i, &first, &last);
	history_len_tmp = get_history_len();
	if (g_bit & FC_OPTION_R)
	{
		history_len_tmp = last;
		last = first;
		first = history_len_tmp;
	}
	if (first < last)
		fc_increase(first, last, g_bit, fd);
	else
		fc_decrease(first, last, g_bit, fd);
	return (0);
}
