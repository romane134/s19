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
