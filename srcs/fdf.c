/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:55 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/12/05 17:22:01 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			display_cmd(t_data *d)
{
	mlx_string_put(d->mlx, d->win, 10, 100, 16185817, "COMMANDES:");
	mlx_string_put(d->mlx, d->win, 10, 200, 16185817, "ZOOM +: +");
	mlx_string_put(d->mlx, d->win, 10, 225, 16185817, "ZOOM -: -");
	mlx_string_put(d->mlx, d->win, 10, 250, 16185817, "RELIEF +: ]");
	mlx_string_put(d->mlx, d->win, 10, 275, 16185817, "RELIEF -: [");
	mlx_string_put(d->mlx, d->win, 10, 300, 16185817, "CHANGE COLOR: 1");
	mlx_string_put(d->mlx, d->win, 10, 325, 16185817, "MOVE Y: UP,DOWN");
	mlx_string_put(d->mlx, d->win, 10, 350, 16185817, "MOVE X: LEFT,RIGHT");
	return (0);
}

int			draw_loop(t_data *data, t_img *i)
{
	while ((i->p.x + 1) < data->tab_w)
	{
		draw_h(i, data);
		if (i->p.y + 1 < data->tab_h)
			draw_v(i, data);
	}
	i->p.x++;
	if (i->p.y + 1 < data->tab_h)
		draw_v(i, data);
	i->p.y++;
	i->p.x = 0;
	return (0);
}

int			bresenham(t_img *img, t_data *data)
{
	img->a.dx = abs(img->p.x2 - img->p.x1);
	img->a.dy = abs(img->p.y2 - img->p.y1);
	img->a.sx = img->p.x1 < img->p.x2 ? 1 : -1;
	img->a.sy = img->p.y1 < img->p.y2 ? 1 : -1;
	img->a.err = (img->a.dx > img->a.dy ? img->a.dx : -img->a.dy) / 2;
	while (42)
	{
		set_pixel(img->p.x1, img->p.y1, img, data);
		if (img->p.x1 == img->p.x2 && img->p.y1 == img->p.y2)
			break ;
		img->a.e = img->a.err;
		if (img->a.e > -img->a.dx)
		{
			img->a.err -= img->a.dy;
			img->p.x1 += img->a.sx;
		}
		if (img->a.e < img->a.dy)
		{
			img->a.err += img->a.dx;
			img->p.y1 += img->a.sy;
		}
	}
	return (0);
}

int			create_img(t_data *data)
{
	t_img	i;

	i.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	i.pixel = mlx_get_data_addr(i.img, &i.bpp, &i.size_line, &i.endian);
	i.zoomx = ((WIN_W - data->tab_w) / data->tab_w) / data->zoom;
	i.zoomx = (i.zoomx <= 0 ? 1 : i.zoomx);
	i.zoomy = ((WIN_H - data->tab_h) / data->tab_h) / data->zoom;
	i.zoomy = (i.zoomy <= 0 ? 1 : i.zoomy);
	i.p.x = 0;
	i.p.y = 0;
	while (data->tab[i.p.y])
		draw_loop(data, &i);
	mlx_hook(data->win, 2, 0, key_hook, data);
	mlx_put_image_to_window(data->mlx, data->win, i.img, 200, 0);
	return (0);
}

int			fdf(char **av)
{
	t_data	data;
	t_list	*map;

	map = NULL;
	data.iw = WIN_W - 200;
	data.alt = 3;
	data.zoom = 4;
	data.side = 0;
	data.updown = 0;
	data.color.r = 126;
	data.color.g = 16;
	data.color.b = 126;
	get_map(av, &map, &data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "42");
	display_cmd(&data);
	create_img(&data);
	mlx_loop(data.mlx);
	return (0);
}
