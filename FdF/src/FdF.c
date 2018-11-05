/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:44:13 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/05 15:59:11 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

int		deal_key(int key, void *param)
{
	ft_putnbr(key);
	if (key == 53)
		exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*param;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test 1");
	mlx_pixel_put(mlx_ptr, win_ptr, 100, 250, 6605050);
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 6605050);

	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
