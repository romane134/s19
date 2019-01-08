/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 11:41:28 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/20 16:22:07 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			print_bits(int color)
{
	int		i;

	i = 32;
	while (i-- > 0)
	{
		if (i % 8 == 0 && i < 31)
			write(1, " ", 1);
		write(1, (color & (i << i)) ? "1" : "0", 1);
	}
}

void			img_put_pixel(int *img, t_coord point/*, int size*/, int color)
{
	if (point.y > 100 && point.y < W_SIZEY &&
			point.x >= 0 && point.x < W_SIZEX)
		img[(int)((point.y - 100) * W_SIZEX + point.x)] = color;
}

static void		draw_sqrt_2(t_all all, int i)
{
	if (all.tt.map->point[i].alt <= all.tt.map->next->point[i].alt)
		draw_line(all.tt.map->point[i], all.tt.map->next->point[i],
			all);
	else
		draw_line(all.tt.map->next->point[i], all.tt.map->point[i],
			all);
}

void			draw_sqrt(t_all all)
{
	int		i;

	while (all.tt.map && !(i = 0))
	{
		while (i < all.tt.map->size)
		{
			if (i < all.tt.map->size - 1)
			{
				if (all.tt.map->point[i].alt <= all.tt.map->point[i + 1].alt)
					draw_line(all.tt.map->point[i], all.tt.map->point[i + 1],
						all);
				else
					draw_line(all.tt.map->point[i + 1], all.tt.map->point[i],
						all);
			}
			if (all.tt.map->next != NULL)
				draw_sqrt_2(all, i);
			i++;
		}
		all.tt.map = all.tt.map->next;
	}
}
