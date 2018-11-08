/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:14:05 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/06 16:34:52 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include "../includes/fdf.h"

void		draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
	int dx;
	int dy;
	int e;

	if ((dx = (x2 - x1)) != 0)
	{
		if (dx > 0)
		{
			if ((dy = (y2 - y1)) != 0)
			{
				if (dy > 0)
				{
					if (dx >= dy)
					{
						e = 0;
						dx = (e = dx) * 2;
						dy *= 2;
						while ((x1++ != x2))
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e -= dy) < 0)
							{
								y1++;
								e += dx;
							}
						}
					}
					else
					{
						e = 0;
						dy = (e = dy) * 2;
						dx *= 2;
						while ((y1++ != y2))
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e -= dx) < 0)
							{
								x1++;
								e += dy;
							}
						}
					}
				}
				else /* dy < 0 && dx > 0*/
				{
					if (dx >= -dy)
					{
						e = 0;
						dx = (e = dx) * 2;
						dy *= 2;
						while ((x1++ != x2))
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e += dy) < 0)
							{
								y1--;
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 7e octant
					{
						e = 0;
						dy = (e = dy) * 2;
						dx *= 2;
						while ((y1-- != y2))
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e += dx) > 0)
							{
								x1++;
								e += dy;
							}
						}
					}
				}
			}
			else // dy = 0 (et dx > 0)
			{
				while ((x1-- != x2))
					mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
			}
		}
		else // dy < 0
		{
			if ((dy = y2 - y1) != 0)
			{
				if (dy > 0)
				{
					if(-dx >= dy)
					{
						e = 0;
						dx = (e = dx) * 2;
						dy *= 2;
						while (x1-- != x2)
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e += dy) >= 0)
							{
								y1++;
								e += dx;
							}
						}
					}
					else
					{
						e = 0;
						dy = (e = dy) * 2;
						dx *= 2;
						while (y1++ != y2)
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e += dx) <= 0)
							{
								x1--;
								e += dy;
							}
						}
					}
				}
				else // dy < 0 (dx < 0)
				{
					if (dx <= dy)
					{
						e = 0;
						dx = (e = dx) * 2;
						dy *= 2;
						while (x1-- != x2)
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e -= dy) >= 0)
							{
								y1--;
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 6e octant
					{
						e = 0;
						dy = (e = dy) * 2;
						dx *= 2;
						while (y1-- != y2)
						{
							mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
							if ((e -= dx) >= 0)
							{
								x1--;
								e += dy;
							}
						}
					}
				}
			}
			else // dy = 0 et dx < 0
			{
				while (x1-- != x2)
					mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
			}
		}
	}
	else // dx = 0
	{
		if ((dy = y2 - y1) != 0)
		{
			if (dy > 0)
			{
				while ((y1++ != y2))
					mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
			}
			else
			{
				while ((y1-- != y2))
					mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
			}
		}
	}
}
