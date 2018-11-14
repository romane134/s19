/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:39:58 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/08 20:56:19 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>
# define DEPART 250

void		init_point(t_coord *point)
{
	point->x = DEPART + 300;
	point->y = DEPART;
	point->b = 0.78; //45 deg
}

char		**ft_read_fdf(int fd)
{
	int i;
	char *line;
	char **tab;
	char *str;
	int j;

	j = 0;
	i = 0;
	if (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		free (line);
		return (tab);
	}
	return (0);
}

t_line    *init_map(t_window window)
{
	t_line    *lst_map;
	t_line    *begin_lst;
	t_coord    current;
	int        fd;
	char			*tmp;
	fd = open("10-70.fdf", O_RDONLY);
	init_point(&current);
	lst_map = (t_line*)malloc(sizeof(t_line));
	begin_lst = lst_map;
	while ((lst_map->tab = ft_read_fdf(fd)))
	{
		lst_map->size = 0;
		while (lst_map->tab[lst_map->size]) //taille de la ligne
			lst_map->size++;
		lst_map->point = (t_coord*)malloc(sizeof(t_coord) * lst_map->size);
		set_point(&current, lst_map, window);

		lst_map->next = (t_line*)malloc(sizeof(t_line));
		tmp = lst_map->next;
		lst_map = lst_map->next;
	}
	tmp = NULL;
	return (begin_lst);
}
