/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 02:29:27 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/20 11:33:08 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

int			degrade(double percent, int color1, int color2)
{
	int red;
	int blue;
	int green;

	if (percent > 1.0)
		return (color2);
	else if (percent < 0)
		return (color1);
	red = (1.0 - percent) * (color1 >> 16) + percent * (color2 >> 16);
	green = (1.0 - percent) * (color1 >> 8 & 0xff) + percent *
		(color2 >> 8 & 0xff);
	blue = (1.0 - percent) * (color1 & 0xFF) + percent * (color2 & 0xff);
	return (blue | green << 8 | red << 16);
}

void		ft_fix_color(t_coord *point, t_param *param)
{
	double percent;

	percent = (double)abs(point->alt) / (double)param->max;
	if (point->alt < 0)
	{
		if (percent < 0.5)
			point->color = degrade(percent * 2, param->color_limit[2],
					param->color_limit[1]);
		else
			point->color = degrade((percent - 0.5) * 2, param->color_limit[1],
					param->color_limit[0]);
	}
	else
	{
		if (percent < 0.5)
			point->color = degrade(percent * 2, param->color_limit[2],
					param->color_limit[3]);
		else
			point->color = degrade((percent - 0.5) * 2, param->color_limit[3],
					param->color_limit[4]);
	}
}

int			choose_color(double percent, double contraste)
{
	int ret;

	if (percent < (1.0 / 6.0))
		ret = degrade(percent * 6, 0XFF, 0xFFFF);
	else if (percent < (1.0 / 3.0))
		ret = degrade((percent - 1.0 / 6) * 6, 0xFFFF, 0xFF00);
	else if (percent < 0.5)
		ret = degrade((percent - 1.0 / 3) * 6, 0xFF00, 0xFFFF00);
	else if (percent < (1.0 / 3.0 * 2.0))
		ret = degrade((percent - 0.5) * 6, 0xFFFF00, 0xFF0000);
	else if (percent < (1.0 / 6.0 * 5.0))
		ret = degrade((percent - 1.0 / 6 * 4) * 6, 0xFF0000, 0xFF00FF);
	else
		ret = degrade((percent - 1.0 / 6 * 5) * 6, 0xFF00FF, 0xFF);
	if (contraste < 0.8)
		return (degrade((1.0 - (contraste) * (1.23)), ret, WHITE));
	return (ret);
}

void		ft_draw_square(t_coord point, int size, int color, t_all *all)
{
	t_coord	point1;

	point1.y = size;
	while (point1.y--)
	{
		point1.x = size;
		while (point1.x--)
			mlx_pixel_put(all->wdw.mlx_ptr, all->wdw.win_ptr, point1.x +
					point.x, point1.y + point.y, color);
	}
}
