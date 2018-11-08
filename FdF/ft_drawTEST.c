/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:43:22 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/08 18:15:18 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

void		draw_sqrt(int x, int y, char *mlx_ptr, char *win_ptr)
{
	int		size_x;
	int		size_y;
	int		stock;
	double	B;
	int		x2;
	int		y2;
	int		x1;
	int		y1;

	B = 0.698132;
	stock = x;
	size_x = 260;
	size_y = 300;
	while (y <= size_y)
	{
		x = stock;
		while (x <= size_x)
		{
			if (y != size_y)
				draw_line(x, y, x, (y + 20), mlx_ptr, win_ptr);
			if (x != size_x)
				draw_line(x, y, (x + 20), y, mlx_ptr, win_ptr);
			x += 20;
		}
		y += 20;
	}
	x = 140;
	y = 140;
	while (y != 180)
	{
		x = 140;
		if ((x <= 160))
		{
			x1 = (x - (20 * cos(B)));
			y1 = (y - (20 * sin(B)));
			x += 20;
			x2 = (x - (20 * cos(B)));
			y2 = (y - (20 * sin(B)));
			draw_line(x1, y1, x2, y2, mlx_ptr, win_ptr);
			draw_line(x1, y1, x1, (y1 + 20), mlx_ptr, win_ptr);

		}
		x = 140;
		y += 20;
		x1 = (x - (20 * cos(B)));
		y1 = (y - (20 * sin(B)));
		x += 20;
		x2 = (x - (20 * cos(B)));
		y2 = (y - (20 * sin(B)));
		draw_line(x1, y1, x2, y2, mlx_ptr, win_ptr);
		draw_line(x1, y1, x1, (y1 + 20), mlx_ptr, win_ptr);
	}


}

void		draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
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
	mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
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
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
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
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
		}
	}
}
