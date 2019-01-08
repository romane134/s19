/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:14:27 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/20 16:23:02 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	void	deal_mouse3(int x, int y, t_all *fdf/*, void *param*/)
{
	x -= 70;
	y -= W_SIZEY - (300 + 70);
	fdf->tt.color_change = 1;
	if (fdf->palette.data[y * 300 + x] != DARK_RED)
	{
		fdf->tt.color_limit[fdf->tt.flag_square] = fdf->palette.data
			[y * 300 + x];
		change_color_limit(fdf);
	}
}

int			deal_mouse2(int x, int y, void *param)
{
	t_all	*fdf;

	if (((t_all*)param)->press == 1)
	{
		fdf = (t_all*)param;
		if (!fdf->tt.color_change && x > 400)
		{
			fdf->tt.departx -= fdf->last_x - x;
			fdf->tt.departy -= fdf->last_y - y;
			fdf->last_x = x;
			fdf->last_y = y;
		}
		else if (x >= 70 && x < 370 && y >= W_SIZEY - (300 + 70) &&
				y < W_SIZEY - (300 + 70) + 300)
			deal_mouse3(x, y, fdf/*, param*/);
		make_change((t_all*)param);
	}
	return (0);
}

int			deal_mouse(int button, int x, int y, void *param)
{
	t_param tt;

	tt = (*(t_all*)param).tt;
	if (button == 5 || button == 4)
	{
		(*(t_all*)param).tt.ecart += -1 * (button == 5) + 1 * (button == 4);
		(*(t_all*)param).tt.ecart = ft_bigger(1, (*(t_all*)param).tt.ecart);
		tt = (*(t_all*)param).tt;
		make_change(param);
	}
	else if (button == 1)
	{
		is_a_square(x, y, (t_all*)param);
		if (!((t_all*)param)->press)
			((t_all*)param)->press = 1;
		else
			((t_all*)param)->press = 0;
		((t_all*)param)->last_y = y;
		((t_all*)param)->last_x = x;
	}
	return (0);
}
