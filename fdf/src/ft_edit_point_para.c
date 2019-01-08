/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_point_para.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:19:31 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/20 16:23:30 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

#define LIMIT 255

#include <stdio.h>

void		set_point_para(t_coord *current, t_param *param)
{
	int i;
//	int ec_x;

	i = -1;
	while (++i < param->map->size)
	{
		param->map->point[i].x = current->x;
		param->map->point[i].y = current->y;
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

void		ft_rotate_para(t_param *param)
{
	t_line		*begin_lst;
	int			i;
//	int			tmp_x;

	begin_lst = param->map;
	while (param->map)
	{
		i = -1;
		while (++i < param->map->size)
		{
			param->map->distance[i].x = param->centre.x - param->map->
				point[i].x;
			param->map->point[i].x = param->centre.x + param->map->
				distance[i].x * cos(param->rot) +
				param->map->point[i].alt * param->zoom * sin(param->rot);
			param->map->point[i].y -= param->map->point[i].alt * param->zoom;
		}
		param->map = param->map->next;
	}
	param->map = begin_lst;
}

void		calcul_point_para(t_param *param/*, float *zoom*/)
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
		set_point_para(&current, param);
		param->map = param->map->next;
	}
	calcul_centre(param);
	param->map = begin_lst;
	ft_rotate_para(param);
}
