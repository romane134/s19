/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:17:38 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/20 13:21:58 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

int			is_a_square(int x, int y, t_all *all)
{
	int		ret;

	ret = -1;
	if (x < PX_SQRT1 + 20 && x >= PX_SQRT1 &&
			y < PY_SQRT1 + 20 && y >= PY_SQRT1)
		ret = 0;
	else if (x < PX_SQRT2 + 20 && x >= PX_SQRT2 &&
			y < PY_SQRT2 + 20 && y >= PY_SQRT2)
		ret = 1;
	else if (x < PX_SQRT3 + 20 && x >= PX_SQRT3 &&
			y < PY_SQRT3 + 20 && y >= PY_SQRT3)
		ret = 2;
	else if (x < PX_SQRT4 + 20 && x >= PX_SQRT4 &&
			y < PY_SQRT4 + 20 && y >= PY_SQRT4)
		ret = 3;
	else if (x < PX_SQRT5 + 20 && x >= PX_SQRT5 &&
			y < PY_SQRT5 + 20 && y >= PY_SQRT5)
		ret = 4;
	if (ret != -1)
		all->tt.flag_square = ret;
	return (ret);
}

t_coord		this_point(int x, int y)
{
	t_coord	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

#define SIZE_SQRT 20

void		change_color_limit(t_all *all)
{
	int		color;

	color = all->tt.color_limit[all->tt.flag_square];
	if (!all->tt.flag_square)
		ft_draw_square(this_point(PX_SQRT1, PY_SQRT1), SIZE_SQRT, color, all);
	else if (all->tt.flag_square == 1)
		ft_draw_square(this_point(PX_SQRT2, PY_SQRT2), SIZE_SQRT, color, all);
	else if (all->tt.flag_square == 2)
		ft_draw_square(this_point(PX_SQRT3, PY_SQRT3), SIZE_SQRT, color, all);
	else if (all->tt.flag_square == 3)
		ft_draw_square(this_point(PX_SQRT4, PY_SQRT4), SIZE_SQRT, color, all);
	else if (all->tt.flag_square == 4)
		ft_draw_square(this_point(PX_SQRT5, PY_SQRT5), SIZE_SQRT, color, all);
}
