/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:43:22 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/08 20:49:12 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"
void    draw_sqrt(t_window window, t_line *lst_map)
{
	lst_map = init_map(window);
	int i;

	i = 0;
	while (lst_map)
	{
		while(i < lst_map-> size - 1)
		{
			draw_line(lst_map->point[i].x, lst_map->point[i].y, lst_map->point[i + 1].x, lst_map->point[i + 1].y, window);
			draw_line(lst_map->point[i].x, lst_map->point[i].y, lst_map->next->point[i].x, lst_map->next->point[i].y, window);
			i++;
		}
		lst_map = lst_map->next;
	}
}

void      set_point(t_coord *current, t_line *lst_map, t_window window)
{
	int i = 0;
	int alt;

	while (i < lst_map->size)
	{
		alt = ft_atoi(lst_map->tab[i]);
		((alt < 0) ? (neg == -1) : (neg == 1));
		lst_map->point[i].x = current->x - (alt * cos(current->b)) /*- current->y / 2 * sin(current->b)*/;
		lst_map->point[i].y = current->y - (alt * sin(current->b) * neg) /*+ current->x / 4 * cos(current->b)*/;
		if (alt > 0)
			mlx_pixel_put(window.mlx_ptr, window.win_ptr, lst_map->point[i].x, lst_map->point[i].y, 7667971);
		else
			mlx_pixel_put(window.mlx_ptr, window.win_ptr, lst_map->point[i].x, lst_map->point[i].y, 13369103);
		mlx_pixel_put(window.mlx_ptr, window.win_ptr, current->x, current->y, 1233151);
		i++;
		current->x += 20;
	}
	current->x = DEPART + 300;
	current->y += 20;
}

void		draw_line(int x1, int y1, int x2, int y2, t_window window)
{
	int		dx;
	int		dy;
	int		xincr;
	int		yincr;
	int		erreur;
	int		e;;

	dx = abs(x2-x1);
	dy = abs(y2-y1);
	((x1 < x2) ? (xincr = 1) : (xincr = -1));
	((y1 < y2) ? (yincr = 1) : (yincr = -1));
	mlx_pixel_put(window->mlx_ptr, window->win_ptr, x1, y1, 6605050);
	if(dx > dy)
	{
		erreur = dx / 2;
		e = 0;
		while ((e++) < dx)
		{
			x1 += xincr;
			erreur += dy;
			if(erreur > dx)
			{
				erreur -= dx;
				y1 += yincr;
			}
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, x1, y1, 6605050);
		}
	}
	else
	{
		erreur = dy / 2;
		e = 0;
		while (e++ < dy)
		{
			y1 += yincr;
			erreur += dx;
			if(erreur > dy)
			{
				erreur -= dy;
				x1 += xincr;
			}
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, x1, y1, 6605050);
		}
	}
}
