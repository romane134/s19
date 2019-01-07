/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:43:22 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/08 18:37:55 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

void		draw_sqrt(char *mlx_ptr, char *win_ptr)
{
	char	**tab;
	int		i;
	int		x;
	int		x1;
	int		y1;
	int y;

	y = 50;
	double b;

	b =0.959931 ;
	i = 0;
	x = 0;

	int fd = open ("coucou.fdf", O_RDONLY);
	while ((tab = ft_read_fdf(fd)))
	{
		y1 = (y - (20 * sin(b)));
		printf ("prochaine ligne\n");
		while (tab[i])
		{
			x1 = (x - (20 * cos(b)));
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 193798);

			if (*tab[i] != '0')
			{
				draw_line(x1, y1, (x - 20), y, mlx_ptr, win_ptr); //vers gauche
				while ((tab[i + 1]) && (*tab[i + 1] != '0'))
				{
					draw_line(x1, y1, (x1 + 20), y1, mlx_ptr, win_ptr); //plateau
					x1 += 20;
					x += 20;
					i++;
					if (*tab[i + 1] == '0')
					{
						i--;
						x -= 20;
						x1 -= 20;
						draw_line((x1 + 20), y1, (x + 40), y, mlx_ptr, win_ptr); //vers droite
						break;
					}
				}
			}
			else if ((tab[i + 1]) && (*tab[i + 1] == '0'))
				draw_line(x, y, (x + 20), y, mlx_ptr, win_ptr); //trait
			i++;
			x += 20;
		}
		x = 0;
		i = 0;
		y += 20;
	}
	x = 0;

}
void		draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
	int		dx;
	int		dy;
	int		xincr;
	int		yincr;
	int		erreur;
	int		e;;

	dx = abs(x2-x1);
	dy = abs(y2-y1);
	((x1 < x2) ? (xincr = 1) : (xincr = -1));
	((y1 < y2) ? (yincr = 1) : (yincr = -1));
	mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
	if(dx > dy)
	{
		erreur = dx / 2;
		e = 0;
		while ((e++) < dx)
		{
			x1 += xincr;
			erreur += dy;
			if(erreur > dx)
			{
				erreur -= dx;
				y1 += yincr;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
		}
	}
	else
	{
		erreur = dy / 2;
		e = 0;
		while (e++ < dy)
		{
			y1 += yincr;
			erreur += dx;
			if(erreur > dy)
			{
				erreur -= dy;
				x1 += xincr;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 6605050);
		}
	}
}
