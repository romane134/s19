/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:44:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/20 13:35:13 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define W_SIZEX 2550
# define W_SIZEY 1320
# define DEPARTX W_SIZEX / 2
# define DEPARTY 300

# include <mlx.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "keycode.h"

/*
** couleur de base
*/

# define RED    0XFF0000
# define GREEN  0X00FF00
# define BLUE   0X0000FF
# define YELLOW 0XFFFF00
# define PURPLE 0XFF00FF
# define CYAN   0X00FFFF
# define BLACK  0X000000
# define WHITE  0XFFFFFF

/*
** couleur bonus
*/

# define DARK_RED 0x2E0514
# define DARK_BROWN 0X654321
# define ELECTRIC_BLUE 0X7DF9FF
# define GRAY 0X808080
# define HEART_GOLD 0X808000
# define LAVENDER_BLUE 0XCCCCFF
# define ELECTRIC_ULTRAMARINE 0X3F00FF
# define EGGPLANT 0X614051
# define DOLLAR_BILL 0X85BB65
# define OLIVE 0XBAB86C
# define ORANGE 0XFFA500
# define PINE_GREEN 0X01796F
# define PX_SQRT1 45
# define PY_SQRT1 W_SIZEY / 2 + 220
# define PX_SQRT2 PX_SQRT1 + 68
# define PY_SQRT2 PY_SQRT1
# define PX_SQRT3 PX_SQRT2 + 68
# define PY_SQRT3 PY_SQRT1
# define PX_SQRT4 PX_SQRT3 + 68
# define PY_SQRT4 PY_SQRT1
# define PX_SQRT5 PX_SQRT4 + 68
# define PY_SQRT5 PY_SQRT4

# include <fcntl.h>
# include "../GNL/get_next_line.h"
# include <mlx.h>

typedef struct		s_coord
{
	int				x;
	int				y;
	int				alt;
	unsigned int	color;
}					t_coord;

typedef struct		s_line
{
	char			**tab;
	int				size;
	t_coord			*point;
	t_coord			*distance;
	struct s_line	*next;
}					t_line;

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_window;

typedef struct		s_param
{
	t_line			*map;
	t_line			*l_centre;
	t_window		window;
	t_coord			centre;

	unsigned int	ecart;
	int				max;
	float			zoom;
	double			b;
	double			rot;
	double			roty;
	double			rotz;
	int				d_departx;
	int				d_departy;
	int				departx;
	int				departy;
	int				flag_square;
	int				color_limit[5];
	int				color_change;
	int				lst_size;
}					t_param;

typedef	struct		s_var_p
{
	double			angle;
	double			inc_a;
	int				circ;
	int				i;
	int				i2;
}					t_var_p;

typedef struct		s_var_draw
{
	int				dx;
	int				dy;
	int				xincr;
	int				yincr;
	int				erreur;
	int				e;
}					t_var_draw;

typedef	struct		s_image
{
	void			*img;
	int				*data;
	int				size;
	int				bpp;
	int				a;
}					t_image;

typedef struct		s_all
{
	t_param			tt;
	t_image			image;
	t_window		wdw;
	t_image			palette;
	t_image			square;
	int				projection;
	int				press;
	int				last_x;
	int				last_y;
}					t_all;

/*
** ft_color.c
*/
void				ft_fix_color(t_coord *point, t_param *param);
int					degrade(double percent, int color1, int color2);
int					choose_color(double percent, double contraste);
void				ft_draw_square(t_coord point, int size, int color,
		t_all *all);

/*
** ft_edit_point_iso.c
*/
void				init_point(t_coord *point);
void				set_point(t_coord *current, t_param *param);
void				calcul_point(t_param *param/*, float *zoom*/);
void				ft_rotate(t_param *param);
void				calcul_zoom(t_param *param, int lst_size);

/*
** ft_edit_point_para.c
*/
void				set_point_para(t_coord *current, t_param *param);
void				calcul_point_para(t_param *param/*, float *zoom*/);
void				ft_rotate_para(t_param *param);

/*
** ft_mlx.c
*/
void				make_change(t_all *all);
int					ft_bigger(int val1, int val2);
int					deal_key(int key, void *param);
int					release_btn(int button, int coucou, int salut, void *param);

/*
** ft_mlx_mouse.c
*/
int					deal_mouse(int button, int x, int y, void *param);
int					deal_mouse2(int x, int y, void *param);

/*
** ft_read_fdf.c
*/
int					ft_read_fdf(int fd, t_param *param);
void				calcul_zoom(t_param *param, int lst_size);
void				calcul_centre(t_param *param);
void				init_param(t_param *param);
int					reader(t_param *param, t_line **tmp);
t_param				init_map(t_window window, int fd);

/*
** ft_strsplit_v2.c
*/
int					ft_strsplit_v2(char const *s, char c, char ***new);

/*
** palette.c
*/
void				init_var_circle(t_var_p *var, int size);
int					point_is_valid(t_coord point1, t_var_p *var);
int					create_palette(t_all *all, int size);
void				ft_draw_circle(int size, t_all *all);

/*
** selection_square.c
*/
int					is_a_square(int x, int y, t_all *all);
t_coord				this_point(int x, int y);
void				change_color_limit(t_all *all);

/*
** ft_draw.c
*/
void				draw_line(t_coord point1, t_coord point2, t_all all);
int					delta_color(float percent, t_coord point1, t_coord point2);
void				init_var_draw(t_var_draw *var, t_coord point1,
		t_coord point2);

/*
** draw_2.c
*/
void				img_put_pixel(int *img, t_coord point/*, int size*/, int color);
void				draw_sqrt(t_all all);
void				print_bit(int color);

/*
** get_next_line.c
*/
int					get_next_line(const int fd, char **line);

/*
** ft_title.c
*/
void				make_title(t_window window, t_all *all);

#endif
