/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 23:07:37 by rhunders          #+#    #+#             */
/*   Updated: 2019/01/07 19:05:06 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>
#include <time.h>

#define SIZE_MINX (W_SIZEX - W_SIZEX / 100)
#define SIZE_MINY (W_SIZEY - W_SIZEY / 100)

int			ft_read_fdf(int fd, t_param *param)
{
	char	*line;
//	char	**tab;

	if (get_next_line(fd, &line) > 0)
	{
		param->map->size = ft_strsplit_v2(line, ' ', &param->map->tab);
		free(line);
		return (1);
	}
	return (0);
}

void		calcul_centre(t_param *param)
{
	param->centre = param->l_centre->point[param->l_centre->size
		/ 2];
}

void		init_param(t_param *param)
{
	param->ecart = 100;
	param->b = 0.5;
	param->rot = 3.2;
	param->color_limit[0] = RED;
	param->color_limit[1] = BLUE;
	param->color_limit[2] = CYAN;
	param->color_limit[3] = BLUE;
	param->color_limit[4] = RED;
	param->departx = DEPARTX;
	param->departy = DEPARTY;
	param->flag_square = 2;
}

int			reader(t_param *param, t_line **tmp)
{
	if (param->ecart * param->map->size > SIZE_MINY &&
			param->ecart * param->map->size > SIZE_MINX)
		param->ecart = ((SIZE_MINY < SIZE_MINX) ? SIZE_MINX : SIZE_MINY) /
			(param->map->size + 1);
	if (!(param->map->point = (t_coord*)malloc(sizeof(t_coord) *
					param->map->size)))
		return (0);
	if (!(param->map->distance = (t_coord*)malloc(sizeof(t_coord) *
					param->map->size)))
		return (0);
	ft_memset(param->map->distance, 0, sizeof(t_coord) * param->map->size);
	if (!(param->map->next = (t_line*)malloc(sizeof(t_line))))
		return (0);
	*tmp = param->map;
	param->map = param->map->next;
	param->lst_size++;
	return (1);
}

t_param		init_map(t_window window, int fd)
{
	t_param		param;
	t_line		*begin_lst;
	t_line		*tmp;

	if (!(param.map = (t_line*)malloc(sizeof(t_line))))
		return (param);
	begin_lst = param.map;
	init_param(&param);
	while ((ft_read_fdf(fd, &param)))
		if (!reader(&param, &tmp))
		{
			return (param);
		}
	free(param.map);
	tmp->next = NULL;
	param.map = begin_lst;
	calcul_zoom(&param, param.lst_size / 2);
	if (param.ecart > 1)
		param.ecart /= 2;
	else
		param.ecart = 1;
	calcul_point(&param/*, &param.zoom*/);
	return (param);
}
