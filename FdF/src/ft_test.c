/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:14:05 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/05 16:22:38 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <mlx.h>
#include "../libft/includes/libft.h"

void		draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
	int x;
	int y;
	int Dx,Dy;
	int xincr,yincr;
	int erreur;
	int i;

	Dx = abs(x2-x1);
	Dy = abs(y2-y1);
	if(x1 < x2)
		xincr = 1;
	else
		xincr = -1;
	if(y1 < y2)
		yincr = 1;
	else
		yincr = -1;

	x = x1;
	y = y1;
	if(Dx > Dy)
	{
		erreur = Dx / 2;
		i = 0;
		while (i++ < Dx)
		{
			x += xincr;
			erreur += Dy;
			if(erreur > Dx)
			{
				erreur -= Dx;
				y += yincr;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 6605050);
		}
	}
	else
	{
		erreur = Dy / 2;
		while (i++ < Dy)
		{
			y += yincr;
			erreur += Dx;
			if(erreur > Dy)
			{
				erreur -= Dy;
				x += xincr;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 6605050);
		}
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
	mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, 6605050);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*param;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test 1");
	draw_line(2, 2, 400, 450,  mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
}
