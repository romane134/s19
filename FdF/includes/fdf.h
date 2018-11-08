/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:44:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/08 20:46:55 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
#include <fcntl.h>
#include "../GNL/get_next_line.h"
#include <mlx.h>

typedef struct	s_coord
{
	int		x;
	int		y;
	double	b;
}				t_coord;

typedef struct	s_line
{
	char	**tab;
	int		size;
	t_coord	*point;
	struct s_line *next;
}				t_line;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_window;

int			get_next_line(const int fd, char **line);
int			deal_key(int key, void *param);
void		draw_line(int x1, int x2, int y1, int y2, void *mlx_ptr, void *win_ptr);
//t_line		*draw_sqrt(char *mlx_ptr, char *win_ptr);
char		**ft_read_fdf(int fd);
void		init_point(t_coord *point);
t_line		*init_map(t_window window);


#endif
