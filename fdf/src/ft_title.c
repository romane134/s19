/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_title.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 15:54:20 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/20 16:10:23 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#define SIZE_SQRT 20

static	void	make_title_part3(t_window window, t_all *all)
{
	mlx_string_put(window.mlx_ptr, window.win_ptr, 320, 390,
			LAVENDER_BLUE, "I_KEY");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 150 + (ft_strlen("<    >") /
				2 * 10), 280, LAVENDER_BLUE, "^");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 150 + (ft_strlen("<    >") /
				2 * 10), 300, LAVENDER_BLUE, "v");
	ft_draw_square(this_point(PX_SQRT1, PY_SQRT1), SIZE_SQRT, RED, all);
	ft_draw_square(this_point(PX_SQRT2, PY_SQRT2), SIZE_SQRT, BLUE, all);
	ft_draw_square(this_point(PX_SQRT3, PY_SQRT3), SIZE_SQRT, CYAN, all);
	ft_draw_square(this_point(PX_SQRT4, PY_SQRT4), SIZE_SQRT, BLUE, all);
	ft_draw_square(this_point(PX_SQRT5, PY_SQRT5), SIZE_SQRT, RED, all);
}

static	void	make_title_part2(t_window window, t_image img, t_all *all)
{
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 100);
	mlx_string_put(window.mlx_ptr, window.win_ptr, (W_SIZEX + 400) / 2 -
			(ft_strlen("FDF") / 2 * 10), 35, BLACK, "FDF");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 80, 150, 0XBF112B, "ZOOM :");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 150, 130, LAVENDER_BLUE,
			"- | mouse up");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 150, 170, LAVENDER_BLUE,
			"+ | mouse down");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 80, 240, 0XBF112B,
			"ROTATE:");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 155, 240, LAVENDER_BLUE,
			"<    >");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 80, 290, 0XBF112B,
			"MODI ALT:");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 80, 340, 0XBF112B,
			"PROJECTION PARALLELE:");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 300, 340, LAVENDER_BLUE,
			"P_KEY");
	mlx_string_put(window.mlx_ptr, window.win_ptr, 80, 390, 0XBF112B,
			"PROJECTION ISOMETRIQUE:");
	make_title_part3(window, all);
}

void			make_title(t_window window, t_all *all)
{
	t_image img;

	img.img = mlx_new_image(window.mlx_ptr, W_SIZEX + 400, 100);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size, &img.a);
	img.a = 0;
	while (img.a < (W_SIZEX + 400) * 100)
		img.data[img.a++] = GRAY;
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	img.img = mlx_new_image(window.mlx_ptr, 400, 1220);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size, &img.a);
	img.a = 0;
	while (img.a < 1220 * 400)
		img.data[img.a++] = DARK_RED;
	make_title_part2(window, img, all);
}
