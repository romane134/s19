/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:43:17 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/20 16:44:24 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>
#include <math.h>

void			make_change(t_all *all)
{
	if (all->projection == 0)
		calcul_point(&all->tt/*, &all->tt.zoom*/);
	else
		calcul_point_para(&all->tt/*, &all->tt.zoom*/);
	mlx_destroy_image(all->wdw.mlx_ptr, all->image.img);
	all->image.img = mlx_new_image(all->wdw.mlx_ptr, W_SIZEX, W_SIZEY - 100);
	all->image.data = (int *)mlx_get_data_addr(all->image.img, &all->image.bpp,
			&all->image.size, &all->image.a);
	draw_sqrt(*all);
	mlx_put_image_to_window(all->wdw.mlx_ptr, all->wdw.win_ptr, all->image.img,
			400, 100);
}

static	void	deal_key_2(int key, void *param)
{
	(*(t_all*)param).tt.zoom += -(float)(key == 125) * 0.5 +
		(float)(key == 126) * 0.5;
	make_change((t_all*)param);
}

int				deal_key(int key, void *param)
{
	t_all param_cl;

	param_cl = *(t_all*)param;
	if (key == P_KEY)
	{
		((t_all*)param)->projection = 1;
		make_change(param);
	}
	else if (key == I_KEY)
	{
		((t_all*)param)->projection = 0;
		make_change(param);
	}
	else if (key == 53)
		exit(0);
	else if (key == 126 || key == 125)
		deal_key_2(key, param);
	else if (key == 123 || key == 124)
	{
		((t_all*)param)->tt.rot += -0.05 * (key == 124) + 0.05 *
			(key == 123);
		make_change(param);
	}
	return (0);
}

int				release_btn(int button, int coucou, int salut, void *param)
{
	if (button == 1)
	{
		((t_all*)param)->press = 0;
		((t_all*)param)->last_y = -200;
		((t_all*)param)->last_x = -200;
		((t_all*)param)->tt.color_change = 0;
	}
	return (0);
}
