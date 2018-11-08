/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:44:13 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/08 20:47:07 by rlucas-d         ###   ########.fr       */
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
/*	void	*mlx_ptr;
	void	*win_ptr;*/
	t_window window;
	void	*param;
	t_line	*map;

	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, 1650, 1080, "test 1");
	map = init_map(window);
	mlx_key_hook(window.win_ptr, deal_key, (void *)0);
	mlx_loop(window.mlx_ptr);
}
