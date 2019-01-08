/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:44:43 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/07 19:07:56 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>
#define SIZE_SQRT 20

static	int		ft_open(char **argv)
{
	int fd;

	if (argv[1])
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			write(1, "<Map error>\n", 13);
			return (0);
		}
	}
	else
	{
		write(1, "Usage <filename>\n", 17);
		return (0);
	}
	return (fd);
}

static	void	ft_do(t_all all)
{
	all.image.img = mlx_new_image(all.wdw.mlx_ptr, W_SIZEX, W_SIZEY - 100);
	all.image.data = (int *)mlx_get_data_addr(all.image.img, &all.image.bpp,
			&all.image.size, &all.image.a);
	draw_sqrt(all);
	mlx_put_image_to_window(all.wdw.mlx_ptr, all.wdw.win_ptr, all.image.img,
			400, 100);
	make_title(all.wdw, &all);
	ft_draw_circle(150, &all);
	mlx_key_hook(all.wdw.win_ptr, deal_key, &all);
	mlx_mouse_hook(all.wdw.win_ptr, deal_mouse, &all);
	mlx_hook(all.wdw.win_ptr, MOTIONNOTIFY, BUTTONPRESSMASK,
			deal_mouse2, &all);
	mlx_hook(all.wdw.win_ptr, BUTTONRELEASE, BUTTONRELMASK, release_btn, &all);
	mlx_loop(all.wdw.mlx_ptr);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_all	all;
	t_coord point;

	all.tt.zoom = 2;
	if (argc > 2)
		return (write(1, "usage <filename>\n", 17) & 0);
	all.wdw.mlx_ptr = mlx_init();
	all.wdw.win_ptr = mlx_new_window(all.wdw.mlx_ptr, W_SIZEX + 400,
			W_SIZEY, "FDF");
	point.x = W_SIZEX / 2;
	point.y = W_SIZEY / 2;
	if (!(fd = ft_open(argv)))
		return (0);
	all.tt.d_departx = -200;
	all.tt.d_departy = -200;
	all.press = 0;
	all.tt = init_map(all.wdw, fd);
	all.tt.color_change = 0;
	all.projection = 0;
	if (!all.tt.map)
		return (write(1, "<file error>\n", 13) & 0);
	ft_do(all);
}
