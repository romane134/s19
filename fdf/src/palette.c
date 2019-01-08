/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 02:05:29 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/20 15:40:30 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

void	init_var_circle(t_var_p *var, int size)
{
	var->circ = (double)M_PI * (double)size * (double)size;
	var->inc_a = (2.0 * (double)M_PI) / var->circ;
	var->angle = 0;
	var->i = -1;
}

int		point_is_valid(t_coord point1, t_var_p *var)
{
	return ((int)point1.x < (var->i2 * 2) &&
			(int)point1.x >= 0 &&
			(int)point1.y < (var->i2 * 2) &&
			(int)point1.y >= 0);
}

int		create_palette(t_all *all, int size)
{
	int i;
	int	size_img;

	i = -1;
	size_img = 4 * size * size;
	all->palette.img = mlx_new_image(all->wdw.mlx_ptr,
			2 * size, 2 * size);
	all->palette.data = (int *)mlx_get_data_addr(all->palette.img,
			&all->palette.bpp, &all->palette.size, &all->palette.a);
	while (++i < size_img)
		all->palette.data[i] = DARK_RED;
	all->palette.data[size_img / 2] = WHITE;
	return (size);
}

void	fill_center(t_image img, int size)
{
	int i;
	int i2;

	i = -1;
	i2 = -1;
	while (++i < 20)
		while (++i2 < 50 || !(i2 = -1))
			img.data[((i + size - 10) * size * 2) + (i2 + size - 10)] = WHITE;
}

void	ft_draw_circle(int size, t_all *all)
{
	t_coord point1;
	t_var_p var;

	var.i2 = create_palette(all, size);
	fill_center(all->palette, size);
	while (size)
	{
		init_var_circle(&var, size);
		while (++(var.i) < var.circ)
		{
			point1.x = ((double)var.i2) + ((double)size * cos(var.angle));
			point1.y = ((double)var.i2) + ((double)size * sin(var.angle));
			if (point_is_valid(point1, &var))
				all->palette.data[(int)(point1.y * var.i2 * 2) + point1.x] =
					choose_color((double)var.i / (double)var.circ,
							(double)size / var.i2);
			var.angle += var.inc_a;
		}
		size -= 1;
	}
	mlx_put_image_to_window(all->wdw.mlx_ptr, all->wdw.win_ptr,
			all->palette.img, 45, W_SIZEY - (300 + 70));
}
