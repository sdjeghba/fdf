/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:11:57 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/27 16:49:33 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>
# define ESC 53

typedef struct		s_point
{
	int				x;
	int				y;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}					t_point;

typedef struct		s_algo
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e;
}					t_algo;

typedef struct		s_img
{
	int				*img;
	int				bpp;
	int				size_line;
	int				endian;
	char			*pixel;
	int				i;
	int				spw_btw_pts;
	int				sph_btw_pts;
	t_algo			bres;
	t_point			p;
}					t_img;

typedef struct		s_data
{
	int				win_w;
	int				win_h;
	int				tab_w;
	int				tab_h;
	void			*mlx;
	void			*win;
	int				**tab;
}					t_data;

int					fdf(char **av);

/*
** get_map.c
*/

int					get_map(char **av, t_list **map, t_data *data);
int					fill_coor(t_list *map, t_data *data);
int					check_map(char *str);
int					fill_intab(char **tab, t_data *data, int y);
int					loop_tabatoi(t_list *tmp, t_data *data, int y);

/*
** fdf.c
*/

int					draw_v(t_img *img, t_data *data);
int					draw_h(t_img *img, t_data *data);
int					bresenham(t_img *img, t_data *data);
int					create_img(t_data *data, t_img *img);
int					fdf(char **av);

/*
** tools.c
*/

int					key_hook(int keycode, t_data *e);
void				set_pixel(int x, int y, t_img *img);
int					display_error(char *str);

#endif
