/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:55 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/12/03 13:13:29 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	mlx_key_hook(data->win, key_hook, data);
	mlx_put_image_to_window(data->mlx, data->win, i.img, 0, 0);
	return (0);
}

int			fdf(char **av)
{
	t_data	data;
	t_list	*map;

	map = NULL;
	data.zoom = 4;
	data.side = 0;
	data.updown = 0;
	get_map(av, &map, &data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "42");
	create_img(&data);
	mlx_loop(data.mlx);
	return (0);
}
