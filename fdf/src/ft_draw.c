/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:42:06 by rhunders          #+#    #+#             */
/*   Updated: 2019/01/07 19:07:45 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

void		init_var_draw(t_var_draw *var, t_coord point1, t_coord point2)
{
	var->dx = abs(point2.x - point1.x);
	var->dy = abs(point2.y - point1.y);
	var->xincr = (point1.x < point2.x) ? 1 : -1;
	var->yincr = (point1.y < point2.y) ? 1 : -1;
	var->erreur = (var->dx > var->dy) ? var->dx / 2 : var->dy / 2;
	var->e = 0;
}

int			delta_color(float prct, t_coord point1, t_coord point2)
{
	int		rgb[3];

	return (degrade(prct, point1.color, point2.color));
	if (((point1.color >> 16) & 0xFF) < ((point2.color >> 16) & 0xFF))
		rgb[0] = ((point1.color >> 16) & 0X0000FF) + (((point2.color >> 16)
					& 0X0000FF) - ((point1.color >> 16) & 0X0000FF)) * prct;
	else
		rgb[0] = ((point1.color >> 16) & 0X0000FF) - (((point1.color >> 16)
					& 0X0000FF) - ((point2.color >> 16) & 0X0000FF)) * prct;
	if (((point1.color >> 8) & 0xFF) < ((point2.color >> 8) & 0xFF))
		rgb[2] = ((point1.color >> 8) & 0X0000FF) + (((point2.color >> 8)
					& 0X0000FF) - ((point1.color >> 8) & 0X0000FF)) * prct;
	else
		rgb[2] = ((point1.color >> 8) & 0X0000FF) - (((point1.color >> 8)
					& 0X0000FF) - ((point2.color >> 8) & 0X0000FF)) * prct;
	if (((point1.color) & 0xFF) < ((point2.color) & 0xFF))
		rgb[1] = (point1.color & 0X0000FF) + (((point2.color & 0X0000FF)
					- (point1.color & 0X0000FF)) * prct);
	else
		rgb[1] = (point1.color & 0X0000FF) - (((point1.color & 0X0000FF)
					- (point2.color & 0X0000FF)) * prct);
	return ((rgb[0] << 16) | (rgb[2] << 8) | (rgb[1]));
}

static void	draw_line_3(t_coord *point, t_all all, t_var_draw var, int size_l)
{
	float		nb;
	int			color;

	while ((var.e++) < var.dx)
	{
		point[0].x += var.xincr;
		var.erreur += var.dy;
		if (var.erreur > var.dx)
		{
			var.erreur -= var.dx;
			point[0].y += var.yincr;
		}
		nb = ((float)(float)var.e / (float)size_l);
		if (point[0].color != point[1].color)
			color = delta_color(nb, point[0], point[1]);
		else if (color != (int)point[0].color)
			color = point[0].color;
		img_put_pixel(all.image.data, point[0],/* all.image.size,*/ color);
	}
}

static void	draw_line_2(t_coord *point, t_all all, t_var_draw var, int size_l)
{
	float		nb;
	int			color;

	while (var.e++ < var.dy)
	{
		point[0].y += var.yincr;
		var.erreur += var.dx;
		if (var.erreur > var.dy)
		{
			var.erreur -= var.dy;
			point[0].x += var.xincr;
		}
		nb = ((float)(float)var.e / (float)size_l);
		if (point[0].color != point[1].color)
			color = delta_color(nb, point[0], point[1]);
		else if (color != (int)point[0].color)
			color = point[0].color;
		img_put_pixel(all.image.data, point[0],/* all.image.size,*/ color);
	}
}

void		draw_line(t_coord point1, t_coord point2, t_all all)
{
	t_var_draw	var;
	int			size_l;
	t_coord		point[2];

	point[0] = point1;
	point[1] = point2;
	init_var_draw(&var, point[0], point[1]);
	size_l = sqrt(pow(var.dx, 2) + pow(var.dy, 2));
	if (var.dx > var.dy)
		draw_line_3(point, all, var, size_l);
	else
		draw_line_2(point, all, var, size_l);
}
