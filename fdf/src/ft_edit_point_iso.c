/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_point_iso.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 01:51:30 by rhunders          #+#    #+#             */
/*   Updated: 2019/01/07 19:03:06 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define LIMIT 255

void		init_point(t_coord *point)
{
	point->x = DEPARTX;
	point->y = DEPARTY;
}

void		set_point(t_coord *current, t_param *param)
{
	int		i;
	//int		ec_x;

	i = -1;
	while (++i < param->map->size)
	{
		param->map->point[i].x = (current->x - current->y) * cos(param->b);
		param->map->point[i].y = (current->y + current->x) * sin(param->b);
		if (param->d_departx == 0 && param->d_departy == 0)
		{
			param->d_departx = (param->departx - param->map->point[i].x);
			param->d_departy = (param->departy - param->map->point[i].y);
		}
		param->map->point[i].x += param->d_departx;
		param->map->point[i].y += param->d_departy;
		ft_fix_color(param->map->point + i, param);
		current->x += param->ecart;
	}
	current->x = param->departx;
	current->y += param->ecart;
}

void		ft_rotate(t_param *param)
{
	t_line		*begin_lst;
	int			i;
	//int			tmp_x;

	begin_lst = param->map;
	while (param->map)
	{
		i = -1;
		while (++i < param->map->size)
		{
			param->map->distance[i].x = param->centre.x - param->map->
				point[i].x;
			param->map->point[i].x = param->centre.x + param->map->distance[i].x
				* cos(param->rot) + (param->map->point[i].alt * param->zoom)
				* (sin(param->rot));
			param->map->point[i].y -= param->map->point[i].alt * param->zoom
				* sin(param->b);
		}
		param->map = param->map->next;
	}
	param->map = begin_lst;
}

void		calcul_zoom(t_param *param, int lst_size)
{
	int		i;
	t_line	*lst_map;
	int		i2;

	param->max = 1;
	lst_map = param->map;
	i2 = 0;
	while (lst_map && ++i2)
	{
		i = -1;
		while (++i < lst_map->size)
		{
			lst_map->point[i].alt = ft_atoi(lst_map->tab[i]);
			if (abs(lst_map->point[i].alt) >= param->max)
				param->max = abs(lst_map->point[i].alt);
			if (lst_size && i2 == lst_size && i2++)
				param->l_centre = lst_map;
		}
		lst_map = lst_map->next;
	}
	param->zoom = (param->max < 150.0) ? 150.0 / param->max : 1;
}

void		calcul_point(t_param *param/*, float *zoom*/)
{
	t_coord		current;
	t_line		*begin_lst;

	begin_lst = param->map;
	current.x = param->departx;
	current.y = param->departy;
	param->d_departx = 0;
	param->d_departy = 0;
	while (param->map)
	{
		set_point(&current, param);
		param->map = param->map->next;
	}
	calcul_centre(param);
	param->map = begin_lst;
	ft_rotate(param);
}
